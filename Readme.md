# Mutex Transport

This is just a funny project to transfer data between threads/processes using Mutex as a primary transport.

There are few attempts at the moment:
- UART style transport: Sender sends 1 start bit (true), then 8 data bits, then 1 stop bit (false). Receiver adjusts receiving rate detecting a start bit.
  
  Resulting transfer is quite unstable. I was able to transfer just 1 bit per second, otherwise it looses synchronization.