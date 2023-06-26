# Simulation of Interconnected Processors

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

This project was created for the subject of the second term called PRO2 at the Faculty of Informatics of Barcelona. The goal is to simulate the operation of a multiprocessor architecture, where each processor works exclusively with its own memory and can execute multiple processes simultaneously.

## Actions

1. `configure_cluster`: Reads the cluster processors, their connections, and the memory of each processor. If a previous cluster already existed, it ceases to exist. It is guaranteed that the identifiers of the processors are not repeated. The command supports the short form `cc`. This functionality is used for the initialization of the first cluster.

2. `modify_cluster`: Reads an identifier `p` from a processor in the cluster and a new cluster. If `p` does not exist, or it has processes running, or it has processors, an error message is printed. Otherwise, the new cluster is placed in the position of `p`, thus making the original cluster grow (if `p` was an auxiliary of another processor, the root of the new cluster becomes the corresponding auxiliary of that processor). It is guaranteed that there will be no repetition of identifiers in the resulting modified cluster. The command supports the short form `mc`.

3. `high_priority`: Reads a priority identifier. If a priority with the same identifier already exists in the waiting area, an error message is printed. Otherwise, this priority is added to the waiting area with no pending processes. The command supports the short form `ap`.

4. `low_priority`: Reads a priority identifier. If no priority with the same identifier exists in the waiting area or if it has pending processes, an error message is printed. Otherwise, this priority is removed from the waiting area. The command supports the short form `bp`.

5. `high_wait_process`: Reads the data of a process and a priority identifier. If the priority does not exist in the waiting area or if there is already a process with the same identifier and priority, an error message is printed. Otherwise, the process moves to the waiting area with that priority. The command supports the short form `ape`.

6. `high_processor_processor`: Reads the identifier of a processor and the data of a process. If the processor does not exist in the cluster or already contains a process with the same identifier or the process cannot be placed on the processor, an error message is printed. Otherwise, the process is executed on that processor, and the memory it uses becomes occupied. The process is placed in the smallest position that leaves the tightest slot. The command supports the short form `app`.

7. `low_process_processor`: Reads the identifier of a processor and a process. If the processor does not exist or the process is not on the processor, an error message is printed. Otherwise, the process is removed from the processor. The command supports the short form `bpp`.

8. `send_cluster_processes`: Reads a non-negative integer `n`, and an attempt is made to send `n` pending processes to the cluster. The processes are attempted to be placed in the cluster in order of priority. The oldest processes are attempted to be placed first. The attempts continue until `n` processes have been placed in the cluster or until there are no pending processes left or until all pending processes have been unsuccessfully attempted to be placed. If a process could not be placed, there is no point in retrying to send it to the cluster in the same operation. It is then considered to have been rejected by the cluster. Processes rejected by the cluster are returned to the waiting area. The command supports the short form `scp`.




