#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void searchByName();
void create_words();
void display();

struct word
{
    int flag;
    char s[50];
    int pg;
};
struct word w[10000];


void searchByName()
{

    FILE *fp=fopen("index_f.txt","r");
    char ch[50];
	
    printf("Enter the word to be searched in the index: \n");
    scanf("%s",ch);
	
    char c[50];
    char nl;
    int d;
    int flag=0;
    int count = 0;
    int flag2=0;
	
    while(!feof(fp))
    {
    	//check if count == size of index_f.txt
    	if(count == 1629)
    	{
    		flag2 = 1;
    		break;
    	}
    	//reading word in index_f.txt into the string 'c'
        fscanf(fp,"%s",c);

        //if entered word matches with word in index_f.txt
        if(strcmp(c,ch) == 0)
        {
            printf("Yes, the word %s is present in the index it is found in page numbers : ",ch);
            nl = fgetc(fp);
			
            //printing the page number of all pages in which the word occurs
            while(nl!='\n')
            {
                fscanf(fp,"%d",&d);
                printf("%d    ",d);
                nl=fgetc(fp);
            }
            flag++;
            break;
        }
        //if entered word does not match word in file
        else
        {
            nl=fgetc(fp);
            while(nl!='\n')
            {
                nl=fgetc(fp);
            }
        }
        ++count;
    }
    printf("\n");
    if(flag2 == 1)
    {
    	printf("No, the word is not in index.\n");
    	return 0;
    }
    if(flag == 0)
    {
        printf("No the word %s is not present in the index",ch);
    }
}


/*void display()
{

    for(int i=0;i<sizeof(w)/sizeof(w[0]);i++)
    {
        if(w[i].s)
        printf("%s\n",w[i].s);
    }
}*/

//displays the contents of the  index.txt  file made, with repetitions.
//this issue of duplicate strings is solved by running rm_dp.c
void display()
{
    FILE *fptr;
 
    char filename[100], c;

 
    // Open file
    fptr = fopen("index.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
 
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }
    printf("\n\n");
    
    fclose(fptr);
    return 0;
}

//displays the contents of the final index, with reapeating occurrences removed
void displayIndex()
{
    FILE *fptr;
 
    char filename[100], c;

 
    // Open file
    fptr = fopen("index_f.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
 
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }
 	printf("\n\n");
    fclose(fptr);
    return 0;
}

//populates the array 'w'
void create_words()
{
    FILE* f=fopen("words.txt","r");
    char d[20];
    int count=0;
    
    if(f == NULL){printf("error\n");}
    
    while(!feof(f))
    {

		//reading into d from words.txt
        fscanf(f,"%s",d);
        strlwr(d);

        //populating w[count].s with lowercase words from words.txt
        strcpy(w[count].s,d);
        count++;
    }
    fclose(f);
}

//using binary search to search the array w for the string t
int binary_search(char* t)
{
    int low=0;
    int high=3007;
    int mid;
    char g[20];
	
    while(low<=high)
    {
        mid=(low+high)/2;
        strcpy(g,w[mid].s);

        //strings are equal, meaning string is found
        if(strcmp(g,t)==0)
        {
            return 1;
        }
    
		//string you're searching for is greater than string in middle,
        //so we search the right half of the words
        else if(strcmp(t,g)>0)
        {
            low=mid+1;
        }
        
		//string you're searching for is lesser than string in middle,
        //so we search the left half of the words
        else
        {
            high=mid-1;
        }
    }
    return 0;
}

//function to ensure that the string t contains alphabets only
int test(char *t)
{
    for(int i = 0; i < strlen(t); i++)
    {
        if( !isalpha(t[i]) )
        {
            return 0;
        }
    }
    return 1;
}


//function to test whether the page numbers are getting apended or not
void n_fun()
{
    FILE *fp5=fopen("DDE5.txt","r");
    char ch[50];
    char t,t2;
    int pg_no=-1;
	
	while( !feof(fp5) )
	{
		t2 = fgetc(fp5);
    	if(t2 == 12)
    	{
    		pg_no++;
    	}
	}
	printf("%d",pg_no);
   	printf("Testing complete");
}

//function to convert str to lowercase
void strlwr(char* str)
{
	unsigned char* p = (unsigned char*)str;

	while(*p)
	{
		*p = tolower((unsigned char)*p);
		 p++;
	}
	
}



int main()
{
    
    FILE *fp;
    FILE *fp2;
    fp=fopen("DDE5.txt","r");
    fp2=fopen("index.txt","w");
    
	FILE *fp3=fopen("inter.txt","w");
    if(fp==NULL)
    {
        printf("error1");
    }
    
	create_words();
    char t[50];
    int pg_no=0;
    char p;
    char in;
    int flag=1;

    //populating the inter.txt file
    while(!feof(fp))
    {
        in=fgetc(fp);

        //fputc copies contents from 'in' into  inter.txt
        if(in!='\n'){fputc(in,fp3);}
        else{
        fputc(' ',fp3);}
    }
    fclose(fp3);

    fp3 = fopen("inter.txt","r");
    while( !feof(fp3) )
    {
        p = fgetc(fp3);
        while(p == ' ')
        {
        	p = fgetc(fp3);
        }
        
        //updating page numbers; checking p== 12 because 
        //this is the ascii code of the unique char
        //used to distinguish between pages

        //seeks the pointer to one before current location
        fseek(fp3,-1,SEEK_CUR);
        if(p == 12)
        {
        	pg_no++;
        }

        //write the string
        fscanf(fp3,"%s",t);
        strlwr(t);
        //here, 7 is arbitrarily chosen to limit the numbe rof words in the file
        if((!binary_search(t)) && strlen(t)>7 && test(t))
        {
        	//writing to index.txt in the format of 'string' and its page number
            fprintf(fp2,"%s      %d\n",t,pg_no);
        }
    }
 
    fclose(fp);
    fclose(fp2);
    fclose(fp3);//ok now try the code i sent today on index,txt to generate index_f.txt

    

    int ch;
    
	while(1)
	{
		printf("<----------INTERFACE---------->\n");
   	 	printf("1.Display the generated index by page number order.\n");
    	printf("2.Search for a word in the index.\n");
    	printf("3.Display the words by occurence.\n");
		printf("Enter your choice: \n\n");
    	scanf("%d",&ch);
    	
		switch(ch)
    	{
        	case 1:
            	display();
            	break;
        	case 2:
            	searchByName();
            	break;
        	case 3:
        		displayIndex();
        		break;
    	}
    }
    
}

