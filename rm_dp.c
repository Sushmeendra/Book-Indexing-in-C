#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct word
{
	int pg;
	char s[50];
	int flag;
};
int main()
{
	//set this equal to the size of index.txt
	struct word w[15561];
	
	int count=0;
	FILE* fp=fopen("index.txt","r");
	
	while(!feof(fp))
	{
		//read the word and store in w's s
		fscanf(fp,"%s",w[count].s);
		
		//read the page number and store in w's pg
		fscanf(fp,"%d",&w[count].pg);
		
		w[count].flag=0;
		count++;
	}
	remove_duplicates(w);
}

void remove_duplicates(struct word w[])
{
    int y=0;

	char ch[50];
	//creating a new file to store words without duplicates
	FILE *fp2=fopen("index_f.txt","w");
	
	for(int i=0;i<15560;i++)
	{
		if(w[i].flag==0)
		{
			//reading the first word in w into ch
			strcpy(ch,w[i].s);

			//writing  word, page number into index_f.txt
			fprintf(fp2,"%s    %d",ch,w[i].pg);

			//y = page number of word 'i'
			y=w[i].pg;
			
			for(int j=i+1;j<15561;j++)
			{
				//checking strings in w for equality
				//j changes each iteration, but i reamins same
				//so we are comparing first word in w with every other word in w
				if(strcmp(w[j].s,w[i].s)==0)
				{
					//if the words are the same but the page numbers are different
				    if(y!=w[j].pg)
				    {
						fprintf(fp2,"    %d",w[j].pg);
						y=w[j].pg;
					}
					w[j].flag=1;
				}
			}
			fprintf(fp2,"\n");

		}
	}

	fclose(fp2);
}
