<!-- Program Description -->
## About the program

* Movie theater seating challenge with social distancing
* Written in C

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- Instuctions to compile and run -->
### Instuctions to compile and run

* Compile using a C compiler such as cc, gcc, etc. (ex. "cc seating.c -o execName").
* User should run the program with the name of the input file as the 2nd command line argument (executable name first) and the name of the desired output file name as the third command line argument (ex. execName input.txt output.txt).
* The input file should be formattted as "R000 #" on each line, where the the reservation number should follow after "R" and follow the format: 001, 002, ... , 010. Also, the number of seats to reserve for that reservation should follow the reservation number, be separated by a single space, and can only be 3 digits at most.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Assumptions -->
## Assumptions

* I assumed patrons would be most satisfied sitting in (or as close as possible to) the middle two rows and sitting together (sitting together being a higher priority). 
* I assumed that the input file containing the reservations requests would be well formatted. Meaning that Rservations would be in the order that they were received (first being at the top and so on), the input file will be formattted as "R000 #" followed by a space and then the number of patrons (3 digits at most), and the max number of characters on a line would be 8 (ex. R001 200).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- Algorithm Description -->
## Algorithm Description

* Start by checking if there are enough unoccupied seats in the theater to accommodate the current reservation. If no, a message informing the patron that enough seats are not available is printed to the output file. If yes, continue in booking process for current reservation.
* Next, search for the row closest to the middle two rows (E & F) that can seat the current group together. 
* If a row to seat the entire group together is found, they are seated starting from the left most available column and moving right. The 3 seats (or less if at the end of the row) next to the last patron will be marked as occupied for safety purposes.
* If a row to seat the entire group together is not found, the row with the largest number of open seats is determined and most number of patrons from that group are seated in that row. The algorithm then recurses with the patrons that still need to be seated and will end once all have been seated (won't recurse infinitely since it is checked that the total number of seats to accommodate the reservation are available before attempting to seat patrons).

<p align="right">(<a href="#top">back to top</a>)</p>
