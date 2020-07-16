#!/bin/bash

while true;
do
  echo "Please enter a command:";
  read command;

  if [ "$command" == "random" ]
  then
    echo "";
    echo "Please enter the length of the random trace:";
    read lenOfRandTrace;
    echo "Please enter the maximum page number:";
    read maxPageNum;
    echo "Please eneter a random seed:";
    read randSeed;
    echo "Please enter the cache size:";
    read cacheSize;
    echo "Please enter the replacement policy you wish to have:";
    read policy;

    addresses="$(./generate_random_trace.py $lenOfRandTrace $maxPageNum $randSeed)";

    ./paging-policy.py -C $cacheSize -p $policy -a $addresses -c;

    exit 0;

  elif [ "$command" == "locality" ]
  then
    echo "";
    echo "Please enter the length of the trace with some locality:";
    read lenOfTrace;
    echo "Please eneter a random seed:";
    read randSeed;
    echo "Please enter the cache size:";
    read cacheSize;
    echo "Please enter the replacement policy you wish to have:";
    read policy;

    addresses="$(./generate_trace_with_locality.py $lenOfTrace $randSeed)";

    ./paging-policy.py -C $cacheSize -p $policy -a $addresses -c;

    exit 0;

  elif [ "$command" == "valgrind" ]
  then
    echo "transforming data...";

    valgrind --tool=lackey --trace-mem=yes --log-file="valgrind_out.txt" ls;
    tail -n +7 valgrind_out.txt > temp.txt;
    head -n -23 temp.txt > valgrind_out.txt;
    rm temp.txt;

    cat valgrind_out.txt | awk '{ print $2}' | cut -f1 -d"," > transformed_valgrind_out.txt;
    ./determine_vpn.py > valgrind_vpns.txt;
    rm transformed_valgrind_out.txt;

    addresses=$(cat valgrind_vpns.txt | head -n 50);

    rm valgrind_out.txt;
    rm valgrind_vpns.txt;

    echo "done.";
    echo "";

    echo "Please enter cache size:";
    read cache_size;
    echo "Please enter the policy you whish to have:";
    read policy;

    ./paging-policy.py -C $cache_size -p $policy -a $addresses -c;

    echo "done.";
    exit 0;

  elif [ "$command" == "help" ]
  then
    echo "";
    echo "available commands:";
    echo "";
    echo "random         --------------- generates a random trace and runs paging-policy.py.";
    echo "locality       --------------- generates a trace with some locality and runs paging-policy.py.";
    echo "valgrind       --------------- generates a virtual page reference stream from a real application and runs paging-policy.py.";
    echo "quit           --------------- exits the programm.";
    echo "";

  elif [ "$command" == "quit" ]
  then
    exit 0;

  else
    echo "";
    echo "Unknown command! - enter 'help' for help text.";
  fi

done
