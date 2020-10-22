#!/bin/bash

echo -e "make:";

make;

echo -e "\nremove old content of tlb_cost_data.txt...";
echo -n "" > tlb_cost_data.txt;
echo -e "removed old content of tlb_cost_data.txt.";

MAX_NUM_OF_PAGES=2048;
NUM_OF_TRIALS=100000000;

echo -e "\nNUM_OF_TRIALS = $NUM_OF_TRIALS";
echo -e "MAX_NUM_OF_PAGES = $MAX_NUM_OF_PAGES\n";

numOfPages=1;
while [ "$numOfPages" -le "$MAX_NUM_OF_PAGES" ];
do
  echo "gathering data for numOfPages: $numOfPages...";
  time=$(./tlb $numOfPages $NUM_OF_TRIALS | cut -d " " -f 2 | tr -d '\n');
  echo "$numOfPages $time" >> tlb_cost_data.txt;
  numOfPages=$[$numOfPages * 2];
done

echo -e "finished grathering data.\n";
echo "make clean:";

make clean;

python plot_graph.py
