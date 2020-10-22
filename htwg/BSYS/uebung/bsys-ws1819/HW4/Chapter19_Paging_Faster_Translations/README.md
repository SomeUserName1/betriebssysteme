# Homework (Measurement)

In this homework, you are to measure the size and cost of accessing
a TLB. The idea is based on work by Saavedra-Barrera [SB92], who developed a
simple but beautiful method to measure numerous aspects of cache hierarchies,
all with a very simple user-level program. Read his work for more details.

The basic idea is to access some number of pages within a large datastructure
(e.g., an array) and to time those accesses. For example, let’s say the TLB size
of a machine happens to be 4 (which would be very small, but useful for the
purposes of this discussion). If you write a program that touches 4 or fewer
pages, each access should be a TLB hit, and thus relatively fast. However, once
you touch 5 pages or more, repeatedly in a loop, each access will suddenly jump
in cost, to that of a TLB miss. The basic code to loop through an array once
should look like this:

```
int jump = PAGESIZE / sizeof(int);

for (i = 0; i < NUMPAGES * jump; i += jump) {
  a[i] += 1;
}
```

In this loop, one integer per page of the array `a` is updated, up to the
number of pages specified by `NUMPAGES`. By timing such a loop repeatedly (say,
a few hundred million times in another loop around this one, or however many
loops are needed to run for a few seconds), you can time how long each access
takes (on average). By looking for jumps in cost as `NUMPAGES` increases, you can
roughly determine how big the first-level TLB is, determine whether a
second-level TLB exists (and how big it is if it does), and in general get a
good sense of how TLB hits and misses can affect performance. Figure 19.5 (page
15) shows the average time per access as the number of pages accessed in the
loop is increased. As you can see in the graph, when just a few pages are
accessed (8 or fewer), the average access time is roughly 5 nanoseconds. When 16
or more pages are accessed, there is a sudden jump to about 20 nanoseconds per
access. A final jump in cost occurs at around 1024 pages, at which point each
access takes around 70 nanoseconds. From this data, we can conclude that there
is a two-level TLB hierarchy; the first is quite small (probably holding betwe
en 8 and 16 entries); the second is larger but slower (holding roughly 512
entries).  
The overall difference between hits in the first-level TLB and misses is
quite large, roughly a factor of fourteen. TLB performance matters!
