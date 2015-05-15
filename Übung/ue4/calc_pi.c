#include <stdio.h>

void master() {
    MPI_Status stat , stat2 ;

    int j;
    int intervals = 1000000000;
    double delta,x, pi = 0.0;
    delta = 1.0 / (double)intervals;
    int job = 0;
    //loop

    while ( intervals >= 0 || job > 0 ) {
        // Wait for any incomming message
        MPI_Probe (MPI_ANY_SOURCE , MPI_ANY_TAG , MPI_COMM_WORLD , & stat ) ;
        // Store rank of receiver into slave_rank
        int slave_rank = stat.MPI_SOURCE;
            // Decide according to the tag which type of message we have got
        if ( stat.MPI_TAG == TAG_ASK_FOR_JOB ) {
            MPI_Recv (... , slave_rank , TAG_ASK_FOR_JOB , MPI_COMM_WORLD , & stat2 ) ;
            if (/* there are unprocessed jobs */) {
                // here we have unprocessed jobs , we send one job to the slave
                job++;
                    /* pack data of job into the buffer msg_buffer */
                MPI_Send ( msg_buffer , 1 , slave_rank , TAG_JOB_DATA , MPI_COMM_WORLD );
                /* mark slave with rank my_rank as working on a job */
            } else {
                // send stop msg to slave
                MPI_Send (... , slave_rank , TAG_STOP , MPI_COMM_WORLD);
                job--;
            }
        } else {
            // We got a result message
            MPI_Recv ( result_data_buffer , 1 , slave_rank , TAG_RESULT ,
                       MPI_COMM_WORLD , & stat2 ) ;
            /* put data from result_data_buffer into a global result */
            /* mark slave with rank slave_rank as stopped */
            pi += result_data_buffer;
        }

        intervals--;
    }

    printf ("π = %.10f\n", pi * delta);

}

void slave(rank) {
    int stopped = 0;
    MPI_Status stat , stat2 ;
    do {
        // Here we send a message to the master asking for a job
        MPI_Send (rank , 0 , TAG_ASK_FOR_JOB , MPI_COMM_WORLD ) ;
        MPI_Probe (0 ,TAG_ASK_FOR_JOB , MPI_COMM_WORLD , & stat ) ;
        if ( stat.MPI_TAG == TAG_JOB_DATA ) {
            // Retrieve job data from master into msg_buffer
            MPI_Recv ( msg_buffer , 0, TAG_JOB_DATA , MPI_COMM_WORLD , & stat2 ) ;
            /* work on job_data to get a result and store the result into
            result_buffer */

            x = ((double) msg_buffer - 0.5) * delta;
            pi = 4.0 / (1.0 + (x * x));



            // send result to master
            MPI_Send ( pi ,1 , 0 , TAG_RESULT ,MPI_COMM_WORLD ) ;
        } else {
            // We got a stop message we have to retrieve it
            // But we can ignore the data from the MPI_Recv
            MPI_Recv (ignored , 0, TAG_STOP , MPI_COMM_WORLD ,& stat2 ) ;
            stopped = 1;
        }
    } while ( stopped == 0) ;

}





int main() {

    MPI_Init (& argc , & argv );
    MPI_Comm_rank ( MPI_COMM_WORLD , & rank ) ;
    if ( rank == 0) {
        master () ;
    } else {
        slave (rank) ;
    }

    MPI_Finalize () ;

}



