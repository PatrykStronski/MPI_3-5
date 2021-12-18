#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i;
	int message[2];
	int all_results[3];
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int a[2];
	a[0] = rank;
	srand(rank);
	if (rank != 0) { // Rank 0 receives the messages
		a[1] = (int)(rand() % 100);
		MPI_Send(&a[0], 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
	} else {
		cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 2, MPI_INT, MPI_ANY_SOURCE,
			         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "From process " << message[0] << " received message " << message[1] << endl;
			all_results[i-1] = message[1];
		}
		if (all_results[0] > all_results[1] && all_results[1] > all_results[2]) cout<<"Sequence received is stricly descending"<<endl;
		else cout<<"Sequence received is NOT strictly descending"<<endl;
	} 
	MPI_Finalize();
	return 0;
}
