# Answers

1. -p FIFO -l 200,200,200:
  1) r = 0, t = 200
  2) r = 200, t = 400
  3) r = 400, t = 600
  -p SJF -l 200,200,200: see above..

2. -p FIFO -l 100,200,300:
  1) r = 0, t = 100
  2) r = 100, t = 300
  3) r = 300, t = 600
  -p SJF -l 100,200,300: see above..

3. -p RR -q 1 -l 100,200,300:
  1) r = 0, t = 298
  2) r = 1, t = 499
  3) r = 2, t = 600

4. SJF is like FIFO but with ordering by job length. If the jobs are sorted by length, beginning with the shortest first (or all length being equal), the outcome will be the same.

5. If all jobs have the same length as the time slice (or less), each job will finish in one slice, so the response time will be the same for all policies.

6. The response time increases proportional to the job length:
  1) r = 0
  2) r = 10
  3) r = 60
wow

7. The response time for the nth job is the quantum length times n-1 (wtf is the "worst case" tho..?).
