1) This directory contains following files:
- ping_pong_blocking.c : Sample code for MPI blocking communication call.
- ping_pong_non_blocking.c : Sample code for MPI non blocking call.
- run.sh : Script to compile and test both source codes.
- ping_pong_sample_batch.sh : Sample script to submit batch job.
- README : this file.

2) Both codes by default use process ZERO as the root process. But as mentioned in the assignment doc, you will modify the code to select a root node randomly among the 56 processes.

3) Please note: Use the scripts run.sh to only test the outputs of your program using minimal number of nodes, for example 2 Nodes for 56 processes.
Once you test the programs and verify outputs, use "sbatch" on batch file to submit jobs for different combinations of:
	- "number of nodes (N)" and
	- "tasks per node" (ntasks-per-node)
		:: 56N, 1ntasks-per-node
		:: 28N, 2ntasks-per-node
		:: 14N, 4ntasks-per-node
		:: 7N, 8ntasks-per-node
Beware that resources such as 56 nodes may not be allocated instantly and the jobs may stay pending for more than 24 hours, which is why it is important to verify that you are running the programs correctly before submitting the job.

4) You can check status of your jobs using: squeue -u <user_name>

5) Since the scripts run.sh are just for testing, they do not use process pinning parameters while running programs.
   Process pinning calls are added in the batch job script. Reference for process pinning and the parameter values can be found here:
	> https://www.open-mpi.org/doc/v2.0/man1/mpirun.1.php#sect9
	> https://www.open-mpi.org/faq/?category=tuning#using-paffinity-v1.4
	
	Note that you only need to play with "map-by" and "bind-to" parameters.

6) Both sample codes have variable 'N' defined. Modify its value to adjust your data size. A 'char' is usually 1 Byte and a 'double' being 8 Bytes.