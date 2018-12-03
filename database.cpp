//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------
//reads one record entry from account file into a Account record structure
void readFile(AccountRecord * account, std::ifstream & accFile);

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                      // Record number

	 string inputCheck = "none";


    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	 // acctFile.open("accounts.dat");
	 if(!acctFile.is_open())
	 {
      cout<<"file "<< acctFile <<" could not be opened.\n";
      cout<<"Program Terminating...\n";
      return 0;
    }

	 for(int i = 0; !acctFile.eof() ; i++)
	 {

		readFile(&acctRec, acctFile);

		if(acctFile.eof())
			break;
	

		entry.acctID = acctRec.acctID;
		entry.recNum = i;
		
		index.insert(entry);
	 }


    // Output the account IDs in ascending order.
	 cout << endl << "Account IDs :" << endl;
	 index.writeKeys();
	 cout << endl;
	
    // Clear the status flags for the database file.
    acctFile.clear();
	 acctFile.seekg(0, ios::beg);


    // Read an account ID from the keyboard and output the
    // corresponding record.

	 cout << "Enter account ID : ";


	 while( getline(cin, inputCheck) && inputCheck.length() > 0 )
	 {
		istringstream( inputCheck )>>searchID;
		inputCheck.clear();

		cout<<"search ID:  "<<searchID<<endl;
	 	if( !index.retrieve(searchID, entry) )
		{
			cout<<"invalid account ID\n";
			cout << "Enter account ID : ";
			continue;
		}
	
		for(int i = 0; i< entry.recNum + 1; i++)
		{
			readFile(&acctRec, acctFile);
		}

		acctFile.clear(); //clear flags for next iteration;
		acctFile.seekg(0, ios::beg); //read again from the beginnning of file

		recNum = entry.recNum; //i don't know why we need a seperat variable you fools hahahahahaha... please don't dock my score thank you 

	  	cout << recNum
     	<< " : " << acctRec.acctID
     	<< " " << acctRec.firstName
     	<< " " << acctRec.lastName
    	<< " " << fixed << setprecision(2) << acctRec.balance<<endl;
	
		cout << "Enter account ID : ";
	 }
}

void readFile(AccountRecord * account, std::ifstream & accFile)
{
	accFile>> account -> acctID;
	accFile>> account	-> firstName;
	accFile>> account -> lastName;
	accFile>> account -> balance;
}



