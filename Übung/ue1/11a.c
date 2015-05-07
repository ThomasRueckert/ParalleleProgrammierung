//Matrix A[N][N]
//Vektor x[N]
//Ergebnis y
for (int i 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
		y[i] = y[i]+A[i][j]*x[j];
	}
}

//Matrix A[N][N]
//Matrix B[N][N]
//Ergebnis C
for (int i 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
		for (int k 0; k < N; k++) {
			C[i][j] += A[i][k]*B[k][j];
		}
	}
}
