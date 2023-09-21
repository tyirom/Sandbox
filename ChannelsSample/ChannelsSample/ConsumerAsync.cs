using System.Threading.Channels;

namespace ChannelsSample
{
    using System;
    using System.Threading.Channels;
    using System.Threading;
    using System.Threading.Tasks;

    public sealed class ConsumerAsync : IDisposable
    {
        private readonly Task _consumerThread;

        public ConsumerAsync()
        {
            _channel = Channel.CreateUnbounded<TaskCompletionSource<int>>();
            _consumerThread = Worker();
        }

        public async Task<int> EnqueueAndGetValue()
        {
            // net461 or before, RunContinuationsAsynchronously may be ignored because of 
            // https://github.com/dotnet/coreclr/issues/2021 and https://blog.stephencleary.com/2012/12/dont-block-in-asynchronous-code.html
            var tcs = new TaskCompletionSource<int>(TaskCreationOptions.RunContinuationsAsynchronously);
            await _channel.Writer.WriteAsync(tcs).ConfigureAwait(false);
            return await tcs.Task.ConfigureAwait(false);
        }

        private async Task Worker()
        {
            await Task.Yield();
            int currentValue = 0;
            try
            {
                while (await _channel.Reader.WaitToReadAsync().ConfigureAwait(false))
                {
                    while (_channel.Reader.TryRead(out var item))
                    {
                        // net461 or before
                        // var t1 = Task.Run(() => item.TrySetResult(Interlocked.Increment(ref currentValue)));
                        // item.Task.Wait();
                        item.TrySetResult(Interlocked.Increment(ref currentValue));
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine($"unexpected exception:{e}");
                _channel.Writer.TryComplete(e);
            }
        }

        private readonly Channel<TaskCompletionSource<int>> _channel;

        private bool _disposed;

        public void Dispose()
        {
            if (_disposed) return;
            var completeSuccess = _channel.Writer.TryComplete();
            _consumerThread.Wait();
            _disposed = true;
        }
    }
}
