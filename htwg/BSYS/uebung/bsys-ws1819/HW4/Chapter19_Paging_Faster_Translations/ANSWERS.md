# Answers

1.  ###### How precise is such a timer?

    The timer gettimeofday() is obsolete as defined by posix 2008.
    The successor timer, clock_gettime(), is much more precise and provides
    a type with nanosecond resolution. The actual resolution is platform and
    clock dependent and can be found out by clock_getres().
    The overhead for a call to clock_gettime also is dependent on the type of
    clock used.

    ###### How long does an operation have to take in order for you to time it precisely?

    As the overhead for a single call to clock_gettime less than a microsecond,
    the measurement sould be done in a loop at least a few thousand times.


2.  ###### Write the program, called tlb.c, that can roughly measure the cost of accessing each page:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;See: tlb.c file.

3.  ###### Write a script in your favorite scripting language to run this program, while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;See: get_tlb_cost_data.sh file.

    ---

    ###### How many trials are needed to get reliable measurements?

    For access to a single page, we found the best results at 100 mio to 1 mrd
    trials, for 1024 pages a few hundred thousand trials are sufficient.

4.  ###### Next, graph the results, making a graph that looks similar to the one above:

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;See: get_tlb_cost_data.sh,
    tlb_cost_data.txt and tlb_size_measurement.png files.  
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(To generate the plot,the `matplotlib` library for python is needed!).

    ---

    ###### Visualization usually makes the data much easier to digest; why do you think that is?

    The different levels of costs are very easy to recognize. Far better than
    just by looking at the numbers.

5.  ######  How can you ensure the compiler does not remove the main loop above from your TLB size estimator?

    As our measurement loop does nothing but unsued side effects, the compiler
    can put away our loop. To avoid this, we can access our array for any
    arbitrary calculation.

6.  ###### To really get good measurements, you have to run your code on just one CPU, instead of letting the scheduler bounce it from one CPU to the next. How can you do that?

    With the function `sched_setaffinity()` we can pin a process always on the
    same specified CPU.

    ###### What will happen if you don’t do this, and the code moves from one CPU to the other?

    We were not able to identify differences to not pinning the process. We are
    not able to tell why this is necessary.

7.  ###### Another issue that might arise relates to initialization. If you don’t initialize the array `a` above before accessing it, the first time you access it will be very expensive, due to initial access costs such as demand zeroing. Will this affect your code and its timing?

    As the extra cost do not repeat, a big number of trials will cancel out these
    effects.

    ###### What can you do to counterbalance these potential costs?

    We pin our process to one cpu and initialize our array. Also we can step
    through our array one time to "warm up" the cache.
