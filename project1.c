
#include <stdio.h>

float price[15];
char seats[15][30];
int seatsSold = 0;

void showSeats();
void initialize();
void checkSeats();
float getSeats();

void main()
{
	int prompt = 0;
	float revenue = 0;

	for (int i = 0; i < 15; i++)
	{
		printf("Enter price for Row %i:", i+1);
		fflush(stdout);
		scanf("%f", &price[i]);
	}
	initialize();
	showSeats();

	while (prompt != 5)
	{
		printf("Type 1 to enter seats.\n");
		printf("Type 2 to show total revenue.\n");
		printf("Type 3 to show total seats sold.\n");
		printf("Type 4 to show total seats available.\n");
		printf("Type 5 to close the screen.\n");

		fflush(stdout);
		scanf("%i", &prompt);

		if (prompt == 1)
		{
			revenue += getSeats();
			showSeats();
		}
		else if (prompt == 2)
		{
			printf("Total revenue is: $%.2f\n", revenue);
		}
		else if (prompt == 3)
		{
			printf("Total seats sold: %i\n", seatsSold);
		}
		else if (prompt == 4)
		{
			checkSeats();
		}
		else if (prompt == 5)
		{
			printf("Shutting down..\n");
			break;
		}
		else
		{
			printf("Invalid input!\n");
		}

	}

}

void showSeats()
{
	printf("\n");
	printf("\t123456789012345687901234567890\n");
	for (int i = 0; i < 15; i ++)
	{
		printf ("Row %i\t",i+1);
		for (int j = 0; j < 30; j++)
		{
			printf("%c",seats[i][j]);
		}
		printf("\n");
	}
}

void initialize()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			seats[i][j] = '#';
		}
	}
}

void checkSeats()
{
	int count = 0;
	for (int i = 0; i < 15; i ++)
	{
		count = 0;
		for (int j = 0; j < 30; j++)
		{
			if (seats[i][j] == '#')
			{
				count++;
			}
		}
		printf("There are %i seats available on row %i", count, i+1);
		printf("\n");
	}
}

float getSeats()
{
	int row, seat, exit;
	exit = 0;
	float ticketPrice = 0;
	float oneTicket = 0;

	while (exit != 1)
	{
		printf("Enter a seat being sold. [Row][Seat Number]");
		fflush(stdout);
		scanf("%i %i", &row, &seat);

		while (seats[row-1][seat-1] == '*' || !(row <= 15 && row >= 1) || !(seat <= 30 && seat >= 1))
		{
			if (seats[row-1][seat-1] == '*')
			{
				printf("Invalid, seats are already taken. Enter new seats.\n");
			}
			else
			{
				printf("Invalid, seats do not exists. Enter new seats.\n");
			}
			fflush(stdout);
			scanf("%i %i", &row, &seat);
		}

		seats[row-1][seat-1] = '*';
		seatsSold++;

		ticketPrice += price[row-1];
		printf("Ticket price for this seat is: $%.2f\n", price[row-1]);

		printf("Press 0 to enter more ticket, else 1 to exit.\n");
		fflush(stdout);
		scanf("%i", &exit);
	}
	printf("Total Sale: $%.2f", ticketPrice);

	return ticketPrice;
}
