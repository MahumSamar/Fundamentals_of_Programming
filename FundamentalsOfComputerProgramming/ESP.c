/***		   End_Semester_Project : BSCS - 9B
Group Members		 1 : Maryam Fatima : 290479
2 : Mahum Samar : 290647
3 : Fatima Seemab : 291310 ****/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define n 150


//global variables//
/*Declared globally as we have to use them in more than 1 functions*/
int found = 0;
int pos = 0;
int i = 0;
int choice = 0;
int j = 0;
int searchby = 0;
FILE* fptr;
char yes[20] = "n";//took array to give error when user enters a string
errno_t err;

struct Item
{
	int ID;
	char description[21];
	int unitCost;
	int salePrice;
	int quantity;
};
struct Item item[n];

//Declairing the Functions//

int mainMenu();
//a Function to print the main menu and to read choice
int enterProducts(FILE* fptr);
//a Function to enter the products into inventory and write in file
int Read(FILE* fptr);
//a Function to read the items from file
void print_on_Screen();
//a Function to print the items read from file
int search();
//a Function to search an item from file and displays it
int update(FILE* fptr);
//a Function to update the quantity,salePrice and costPrice
int overWrite(FILE* fptr);
//a Function to write updated data in file
int delete(FILE* fptr);
//a Function to delete a specific item from inventory
int sold(int);
//a Function to enter the quantity of product sold
int records(FILE* fptr);
//a Function to keep the record of items sold
void moreEnteries();
//a Function to ask user if he/she wants to continue
void found_notFound(int, int);
//a Function to check whether item is found in inventory or not

int check();
//a Function to Prompt user on entering character when asked for integer
void Help();


//main()//
int main()
{
	while (1)
	{
		mainMenu();//function call
		err = fopen_s(&fptr, "inventory.txt", "r+");
		for (int k = 0; k < n; k++)
		{
			item[k].unitCost = 0;
		}//used to empty the array

		Read(fptr);//function call
		if (!err && fptr != NULL)
			fclose(fptr);

		switch (choice)
		{
		case 0:
			break;
		case 1:
			printf("%s\t %s\t %s\t %s\t %s \n", "ID", "description", "unitCost", "salePrice", "quantity");
			print_on_Screen();//function call
			break;
		case 2:
			err = fopen_s(&fptr, "inventory.txt", "a+");
			Read(fptr);//call
			//read the file to get value of 'i+1' i.e. number of items in inventory
			enterProducts(fptr);//call
			if (!err && fptr != NULL)
				fclose(fptr);//close file
			break;
		case 3:
		{
			int loc = search();
			if (found == 1)
			{
				sold(loc);//function call
			}
		}
		break;
		case 4:
			search();//function call

			break;
		case 5:
			err = fopen_s(&fptr, "inventory.txt", "a+");
			delete(fptr);//function call
			if (!err && fptr != NULL)
				fclose(fptr);

			break;
		case 6:
			err = fopen_s(&fptr, "inventory.txt", "a+");
			update(fptr);//function call
			if (!err && fptr != NULL)
				fclose(fptr);

			break;
		case 7:
			err = fopen_s(&fptr, "salerecord.txt", "r+");
			records(fptr);//function call
			if (!err && fptr != NULL)
				fclose(fptr);

			break;
		case 8:
			Help();
			break;
		default:
			printf("\t\t\t   Invalid Choice");
			printf("\n____________________________________________________________________________________\n");
			break;
		}
		if (!(choice == 0))continue;
		else
			break;
	}
	return 0;
}
int mainMenu()
{
	printf("\n____________________________________________________________________________________\n");
	printf("\t\t\t\t Main Menu");
	printf("\n____________________________________________________________________________________\n");
	printf("\n");
	printf("\tI\t\t 1 - Information About Products\n");
	printf("\tN\t\t 2 - Enter Purchase Records\n");//add an item[i]
	printf("\tV\t\t 3 - Enter Quantity of Product to be sold\n");
	printf("\tE\t\t 4 - Search For Record \n");
	printf("\tN\t\t 5 - Delete an Item From Store Database\n");
	printf("\tT\t\t 6 - Update Item in Store Database\n");//remove an item[i]
	printf("\tO\t\t 7 - Print Sale Records\n");
	printf("\tR\t\t 8 - Help\n");
	printf("\tY\t\t 0 - Exit\n");
	printf("\n____________________________________________________________________________________\n");
	printf("\t\t\t Enter Your Choice: ");
	choice = check();
	printf("____________________________________________________________________________________\n");
	return choice;
}
void moreEnteries()
{
	//ask user if he wants to enter more items or not.
	do
	{
		printf("\n____________________________________________________________________________________\n");
		printf("\t\t\t More entries [y/n]: ");
		scanf_s(" %19s", &yes, 20);//took array for check

		printf("____________________________________________________________________________________\n");

		if (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'))//check
		{
			printf("\t\t Invalid Entry!\n");
		}//Prompt on invalid entry

	} while (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'));

}
int Read(FILE* fptr)
{
	i = 0;
	while (1)
	{
		int flag = fscanf_s(fptr, "%d", &item[i].ID);
		fscanf_s(fptr, "%s", &item[i].description, _countof(item[i].description));
		fscanf_s(fptr, "%d", &item[i].unitCost);
		fscanf_s(fptr, "%d", &item[i].salePrice);
		fscanf_s(fptr, "%d\n", &item[i].quantity);

		if (flag == EOF)
			break;
		//break from loop when file ends
		i++;
	}
	return 0;
}
int enterProducts(FILE* fptr)
{
	do
	{
		//using function check() for integer input to prompt user on invalid entry
		printf("\n____________________________________________________________________________________\n");
		printf("\t\t\t\t Purchase Records\n");
		printf("____________________________________________________________________________________\n\n");

		printf("\t\t Enter Product ID     : ");
		item[i].ID = check();//read
		for (int k = 0; k < i; k++)
		{
			if (item[i].ID == item[k].ID) {
				printf("\t An Item already has this ID,Please reEnter: ");
				item[i].ID = check();
				break;
			}
			//if some item already has that ID, read ID again
		}
		printf("\t\t Enter Description    : ");
		gets_s(item[i].description, 20);
		gets_s(item[i].description, 20);//read

		for (char* p = &item[i].description; *p; ++p)* p = *p >= 'A' && *p <= 'Z' ? *p | 0x60 : *p;//converting to lower case letters


		printf("\t\t Enter Unit Cost      : ");
		item[i].unitCost = check();//read
		printf("\t\t Enter Sale Price     : ");
		item[i].salePrice = check();//read
		printf("\t\t Enter Quantity       : ");
		item[i].quantity = check();//read
		fprintf(fptr, "%d\t %-8s\t %-9d\t %-8d\t %d\n", item[i].ID, item[i].description, item[i].unitCost, item[i].salePrice, item[i].quantity);
		//print in file
		moreEnteries();//function call

	} while (yes[0] == 'y' || yes[0] == 'Y');


	return 0;
}
void print_on_Screen()
{
	i = 0;
	while (item[i].unitCost != 0)
	{
		printf("%d\t %-8s\t %-9d\t %-8d\t %d\n", item[i].ID, item[i].description, item[i].unitCost, item[i].salePrice, item[i].quantity);
		i++;
	}

}

int search()
{
	char search[21];//local array(confined to this function)
	pos = 0;
	int ID_to_search = 0;//local variable

	printf("How do you want to search\n");
	printf("1. Search by ID \n");
	printf("2. Search by description\n");
	while (1)
	{
		printf("\n____________________________________________________________________________________\n");
		printf("\t\t\t Enter Your Choice: ");
		searchby = check();
		printf("____________________________________________________________________________________\n");

		switch (searchby)
		{
		case 1:

			printf("Enter the product ID : ");
			ID_to_search = check();

			found = 0;
			for (j = 0; j < n; j++)
			{
				if (item[j].ID == ID_to_search)
				{ //comparing IDs 
					found = 1;
					pos = j;
					printf("found\n");
					break;//break from loop when item is found
				}
			}
			found_notFound(found, pos);//call
			break;

		case 2:
			printf("Enter name of the item to search: ");
			gets_s(search, 21);
			gets_s(search, 21);//read name of item

			for (char* p = search; *p; ++p)* p = *p >= 'A' && *p <= 'Z' ? *p | 0x60 : *p;//converting to lower case letters
			//so that even case of entry does not match,it will still find the item

			for (j = 0; j < i; j++)
			{
				if (strcmp(item[j].description, search) == 0)
				{//if name matches then do this
					found = 1;
					pos = j;
					printf("found\n");
					break;//break from loop when item is found
				}
			}
			found_notFound(found, pos);//call
			break;

		default:
			printf("Invalid Choice!\n");//prompt when choice is number, other than 1 or 2
			continue;
		}
		break;//break from loop if case 1 or 2 is true i.e 1
	}

	return pos;
}
void found_notFound(int found, int pos)
{
	if (found == 1)//if found
	{
		printf("%d\t %8s\t %-9d\t %-8d\t %d\n", item[pos].ID, item[pos].description, item[pos].unitCost, item[pos].salePrice, item[pos].quantity);
		//print the item found,on the screen
	}
	else//if not found
	{
		printf("\nThe item is not found in inventory\n");
		//prompt
	}
}
int update(FILE* fptr)
{
	int loc;//local variable
	do
	{
		loc = search();//storing location returned by the function search()
		if (found == 1)
		{
			printf("\n____________________________________________________________________________________\n");
			printf("What do you want to update:\n");
			printf("1 - Sales Price\n2 - Quantity\n");
			printf("\n____________________________________________________________________________________\n");
			printf("\t\t\t Enter Your Choice: ");
			choice = check();
			printf("____________________________________________________________________________________\n");


			switch (choice)
			{
			case 1:
			{
				printf("\t\t\t Enter New Sale Price    : ");
				item[loc].salePrice = check();
				if (!err && fptr != NULL)
					fclose(fptr);
				err = fopen_s(&fptr, "inventory.txt", "w+");
				overWrite(fptr);//function call
				printf("\t\t\t Sale Price Updated Successfuly!\n");
				break;
			}
			case 2:
			{
				int quantity = 0;//local variable

				printf("\t\t Enter Quantity to be added     : ");
				quantity = check();
				item[loc].quantity = item[loc].quantity + quantity;//updated quantity
				do
				{//using this loop as check, if user enters other than 'y' or 'n'
					printf("\n____________________________________________________________________________________\n");
					printf("\t\t Do you want to update cost price too? [y/n]: ");
					scanf_s(" %19s", &yes, 20);

					if (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'))//check
					{
						printf("\t\t Invalid Entry!\n");
						continue;
					}//Prompt on invalid entry
				} while (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'));
				if (yes[0] == 'y' || yes[0] == 'Y')
				{
					int cost = 0;
					printf("\t\t Enter Unit Cost of New Purchase    : ");
					cost = check();
					item[loc].unitCost = (item[loc].unitCost + cost) / 2;//finding average
					printf("\t\t New Unit Cost is    : %d ", item[loc].unitCost);
					printf("\n____________________________________________________________________________________\n");
					printf("\t\t\t Unit Cost Updated Successfuly!");
				}


				if (!err && fptr != NULL)
					fclose(fptr);

				err = fopen_s(&fptr, "inventory.txt", "w+");//opened in write mode
				overWrite(fptr);//since quantity is change now
				break;
			}

			default:
				printf("Invalid Choice!\n");
			}
		}
		moreEnteries();//function call
	} while (yes[0] == 'y' || yes[0] == 'Y');

	return 0;
}
int delete(FILE* fptr)
{
	int loc;//local variable
	loc = search();//storing location returned by the function search()
	do
	{
		printf("\n____________________________________________________________________________________\n");
		printf("\t\t\t Are you Sure [y/n]: ");
		scanf_s(" %19s", &yes, 20);

		if (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'))//check
		{
			printf("\t\t Invalid Entry!\n");
		}//Prompt on invalid entry

		if ((yes[0] == 'y' || yes[0] == 'Y') && found == 1)
		{
			for (; loc < n - 1; loc++)
				item[loc] = item[loc + 1];
			//move items one place backward to the position, from where item was deleted
			fclose(fptr);
			fopen_s(&fptr, "inventory.txt", "w+");
			overWrite(fptr);//opened in write mode to over write the file
			printf("\t An item you selected is DELEATED from inventory");
		}

	} while (!(yes[0] == 'y' || yes[0] == 'Y' || yes[0] == 'n' || yes[0] == 'N'));

	return 0;
}
int overWrite(FILE* fptr)
{
	i = 0;
	while (item[i].unitCost != 0)
	{
		fprintf(fptr, "%d\t %-8s\t %-9d\t %-8d\t %d\n", item[i].ID, item[i].description, item[i].unitCost, item[i].salePrice, item[i].quantity);
		i++;
	}
	return 0;
}
int sold(int loc)
{
	int quantity = 0;//local variable(confined to this function)

	while (1)
	{
		printf("\n____________________________________________________________________________________\n");
		printf("\t\t\t Enter Quantity	: ");
		quantity = check();
		printf("____________________________________________________________________________________\n");

		if (item[loc].quantity < quantity)
		{//if less quantity is available then prompt
			printf("We have only %d quantity in Inventory\n", item[loc].quantity);
			continue;
		}
		item[loc].quantity = item[loc].quantity - quantity;
		printf("\t\t\t Quantity Updated Successfuly!");
		err = fopen_s(&fptr, "inventory.txt", "w+");
		overWrite(fptr);//function call
		if (!err && fptr != NULL)
			fclose(fptr);

		break;
	}

	err = fopen_s(&fptr, "salerecord.txt", "a+");
	if (!err && fptr != NULL) {
		fprintf_s(fptr, "%d\t %-8s\t %-9d\t %-8d\t %d\n", item[loc].ID, item[loc].description, item[loc].unitCost, item[loc].salePrice, quantity);
		fclose(fptr);
	}

	return loc;
}
int records(FILE* fptr)
{

	printf("%s\t %s\t %s\t %s\t %s \n", "ID", "description", "unitCost", "salePrice", "quantity Sold");
	{
		for (int k = 0; k < n; k++)
		{//empty the array, since we are using same array to stiore sale record and inventory data
			item[k].unitCost = 0;
		}
		Read(fptr);//call
		//read data from salerecord.txt
		if (!err && fptr != NULL)
			fclose(fptr);
		print_on_Screen(fptr);//function call

	}
	return 0;
}

int check()
{
	int number = 0;
	char c;
	while (scanf_s("%d", &number) != 1)
	{
		printf("\t\t\t Please enter a \"Number\": ");
		scanf_s("%d", &number);
		while ((c = getchar()) != '\n'&& c != EOF);
		fflush(stdin);
	}
	return number;
}
void Help()
{
	printf("\t\t Hi,Welcome to our INVENTORY MANAGEMENT SYSTEM.\n\n");
	printf("____________________________________________________________________________________\n");
	printf("\t\t\t Main Menu is Explained Below\n");
	printf("____________________________________________________________________________________\n");
	printf("o 1 is about the details of items with their ID,name,cost price,\n   sale price and quantity i.e.Your inventory database.\n\n");

	printf("o 2 is to add a new item in our management system.\n   Press 2 and It will ask you to enter ID, name, price and quantity.\n\n");

	printf("o 3 is for finding an item and then it will ask you how much quantity is sold.\n   First you have to type the name or ID to find it.\n   And if found you have to enter the quantity of sold item.If the quantity you entered\n   is more than which is available\n   It will tell user that we have this quantity present and ask to enter other quantity.\n\n");

	printf("o 4 is for searching an item .Press 3 to enter in search mode.\n   Here you can search an item by either its name or ID.if the item is in\n   store its details will be shown to you.\n\n");

	printf("o 5 is if you have to delete an item from your store management in case if it is expired \n  or you want to do so you have to press 5.The system ask for product and then delete it.\n\n");

	printf("o 6 is about updating.By pressing it you can update quantity and sale price.\n   In case you bought new stock you can simply use it.\n   It calculates average of the two costs.\n\n");

	printf("o 7 is for viewing the records.It will show the records of items that are sold.\n");

}