/* Author: Gurbaksh Gill
 * Date: 10/13/2021
 * Description: Solution to Movie Theater Seating Challenge
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Stores the substring of line starting from/including the character at index i to/including the character at
 * index j in sub.
 */ 
void substr(char *line,char *sub, int i, int j) {
	int k = 0;
	while (i <= j) {
		sub[k] = line[i];
		i++;
		k++;
	}
}

/* Calculates the total number of available seats in the theater */
int seatsAvailable(int rows[]) {
	int i, sum = 0;
	for (i = 0; i < 10; i++) sum += rows[i];
	return sum;
}

/* Function that finds the row closest to the middle with the required availability
 * Returns row number with seats available or -1 if none available */
int findRow(int numSeats, int available[]) {
	int i, rowNum = -1;
	int mid1 = 4;
	int mid2 = 5;
	for (i = 0; i < 5; i++) {
		if (available[mid1] >= numSeats) {
			return mid1;
		} else if (available[mid2] >= numSeats) {
			return mid2;
		}
		mid1--;
		mid2++;
	}
	return rowNum;
}

/* Finds row with most seats available */
int findRowWithMostAvail(int available[]) {
	int i, max = 0;
	for (i = 1; i < 10; i++) {
		if (available[max] < available[i]) max = i;
	}
	return max;
}

/* Marks next three seats or less next to last patron as occupied for safety */
void markNextThree(int theater[][20], int row, int lastPatron, int available[]) {
	int i = 0;
	while (lastPatron < 20 && i < 3) {
		theater[row][lastPatron] = 1;
		i++;
		lastPatron++;
		available[row]--;
	}
}

/* Function that reserves customer seats matrix representing theater */
void bookSeats(int theater[][20], int numSeats, int available[], FILE *output, char *resNum) {
	int lastPatron, rowToSeat, i, col;
	char row, base = 'A';
	/* Start by checking enough seats in row theater[4][] or theater[5][] are available */
	/* If yes, seat in middle row. If no, seat in closest row with numSeats available */
	/* If no rows with seats available, seat patrons with anywhere with available seats */
	if (seatsAvailable(available) < numSeats) {
		fprintf(output, "%s Cannot accommodate request due to number of seats available.\n", resNum);
	} else {
		rowToSeat = findRow(numSeats, available);
		if (rowToSeat != -1) {
			fprintf(output, "%s", resNum);
			row = base + rowToSeat;
			for (i = 0; i < numSeats; i++) {
				col = 20 - available[rowToSeat] + i;
				theater[rowToSeat][col] = 1;
				fprintf(output, " %c%i", row, col+1);
			}
			lastPatron = 20 - available[rowToSeat] + numSeats;
			markNextThree(theater, rowToSeat, lastPatron, available);
			available[rowToSeat] -= numSeats;
			fprintf(output, "\n");
		} else {
			fprintf(output, "%s", resNum);
			rowToSeat = findRowWithMostAvail(available);
			numSeats -= available[rowToSeat];
			row = base + rowToSeat;
			for (i = 0; i < available[rowToSeat]; i++) {
				col = 20 - available[rowToSeat] + i;
				theater[rowToSeat][col] = 1;
                               	fprintf(output, " %c%i", row, col+1);
			}
			available[rowToSeat] = 0;
			if (numSeats > 0) {
				bookSeats(theater, numSeats, available, output, "");
			} else {
				fprintf(output, "\n");
			}
		}
	}
}

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	char *buffer;
	size_t buffSize = 9;
	/* theater array will represent available/occupied seats in theater (0 = available, nonzero = occupied */
	int theater[10][20] = {0};
	int seatsInRows[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
	char reservNum[5];
	char numSeat[4];

	/* Test input/output files were successfully opened */
	if (input == NULL || output == NULL) {
		printf("Error: File cannot be opened.\n");
		exit(1);
	}

	buffer = (char *)calloc(9, sizeof(char));
	if (buffer == NULL) {
		printf("Error: cannot allocate memory for input buffer.\n");
		exit(1);
	}
	getline(&buffer, &buffSize, input);
	while(strlen(buffer) != 0) {
		substr(buffer, reservNum, 0, 3);
		substr(buffer, numSeat, 5, strlen(buffer)-1);	
		/* Booking seats for the current reservation */
		bookSeats(theater, atoi(numSeat), seatsInRows, output, reservNum);
		free(buffer);
		buffer = (char *)calloc(9, sizeof(char));
	        if (buffer == NULL) {
        	        printf("Error: cannot allocate memory for input buffer.\n");
                	exit(1);
        	}
		getline(&buffer, &buffSize, input);
	}
	free(buffer);
	
	fclose(output);
	fclose(input);
	return 0;
}
