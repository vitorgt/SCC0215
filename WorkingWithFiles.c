#include<stdio.h>
#include<stdlib.h>

typedef struct _person{
	char first[20], last[20], email[20], nat[20], age[5];
}person;

void str2arr(person *new, char *buffer){
	int i = 0;
	for(i = 0; i < 20; i++)
		if(new->first[i] != '\n' && new->first[i] != '\0')
			buffer[i] = new->first[i];
	for(i = 0; i < 20; i++)
		if(new->last[i] != '\n' && new->last[i] != '\0')
			buffer[i+20] = new->last[i];
	for(i = 0; i < 20; i++)
		if(new->email[i] != '\n' && new->email[i] != '\0')
			buffer[i+40] = new->email[i];
	for(i = 0; i < 20; i++)
		if(new->nat[i] != '\n' && new->nat[i] != '\0')
			buffer[i+60] = new->nat[i];
	for(i = 0; i < 5; i++)
		if(new->age[i] != '\n' && new->age[i] != '\0')
			buffer[i+80] = new->age[i];
}

void clearbuffer(person *new, char *buf){
	int i = 0;
	for(i = 0; i < 6; i++){
		buf[i] = 0;
		new->first[i] = 0;
		new->last[i] = 0;
		new->email[i] = 0;
		new->nat[i] = 0;
		new->age[i] = 0;
	}
	for(; i < 20; i++){
		buf[i] = 0;
		new->first[i] = 0;
		new->last[i] = 0;
		new->email[i] = 0;
		new->nat[i] = 0;
	}
	for(; i < 85; i++)
		buf[i] = 0;
}

int main(){
	int i = 0, j = 0, op = 0;
	FILE *f;
	char arqname[100], another = 'y', buffer[85];
	person new;
	printf("Type file name: ");
	scanf("%s", arqname);
	while(1){
		printf("1) Create file\n2) Insert data\n3) Print all data\n4) Search by RRN\n5) Terminate\n");
		scanf("%d", &op);
		if(op == 1){
			f = fopen(arqname, "wb");
			fclose(f);
			printf("File successfully created\n");
		}
		if(op == 2){
			while(another == 'y'){
				clearbuffer(&new, buffer);
				printf("Press enter after typing each field\nMax size of fields 20 caracs\nFirst Name: ");
				scanf("%s", new.first);
				printf("Last Name: ");
				scanf("%s", new.last);
				printf("Email: ");
				scanf("%s", new.email);
				printf("Nationality: ");
				scanf("%s", new.nat);
				printf("Age: ");
				scanf("%s", new.age);

				str2arr(&new, buffer);

				f = fopen(arqname, "a+b");
				fseek(f, 0, SEEK_END);
				fwrite(buffer,85,1,f);
				fclose(f);

				printf("Insert another? (y/n)");
				scanf(" %c", &another);
			}
		}
		if(op == 3){
			int rrn = 0;
			f = fopen(arqname, "r+b");
			fseek(f, 0, SEEK_END);
			int size = ftell(f)/85;
			fseek(f, 0, SEEK_SET);
			for(i = 0; i < size; i++){
				printf("RRN: %d\n", rrn++);
				fread(&buffer, 20, 1, f);
				printf("Name: %s ", buffer);
				fread(&buffer, 20, 1, f);
				printf("%s\n", buffer);
				fread(&buffer, 20, 1, f);
				printf("Email: %s\n", buffer);
				fread(&buffer, 20, 1, f);
				printf("Nationality: %s\n", buffer);
				fread(&buffer, 5, 1, f);
				printf("Age: %s\n\n", buffer);
			}
			fclose(f);
		}
		if(op == 4){
			int rrn = 0;
			printf("RRN to look for: ");
			scanf("%d", &rrn);
			f = fopen(arqname, "r+b");
			fseek(f, 0, SEEK_END);
			int size = ftell(f)/85;
			if(rrn >= 0 && rrn < size){
				fseek(f, rrn*85, SEEK_SET);
				printf("RRN: %d\n", rrn);
				fread(&buffer, 20, 1, f);
				printf("Name: %s ", buffer);
				fread(&buffer, 20, 1, f);
				printf("%s\n", buffer);
				fread(&buffer, 20, 1, f);
				printf("Email: %s\n", buffer);
				fread(&buffer, 20, 1, f);
				printf("Nationality: %s\n", buffer);
				fread(&buffer, 5, 1, f);
				printf("Age: %s\n\n", buffer);
			}
			else{
				printf("RRN %d not found\n", rrn);
			}
			fclose(f);
		}
		if(op == 5) break;
	}
	return 0;
}
