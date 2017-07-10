#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int nbcar;
    int i=0;

    FILE* text = NULL;
    text = fopen("descartes.txt", "r");//Replace "descartes.txt" with your text file (the source)
    FILE* dest = NULL;
    dest = fopen("dest.xml","w+");//Will create and write your text + the tags in the "dest.xml" file (the destination)

	/* ---Get the number of characters in the given file--- */
    do{
    nbcar = fgetc(text);
     i+=1;
        } while (nbcar != EOF);

    rewind(text);
    printf("The original text contains %d characters.\n",i );
	/* ----------------------------------------------------- */

    int car; /* //!!\\ INITIAlLY WRITTEN IN FRENCH --> the variable's name is 'car', short for 'caractere', 
	which means character, feel free to change it and its occurrences */
    int tmp1, tmp2;

    fprintf(dest,"<p>");//puts the given tag at the very start of our text

    do{
        car=fgetc(text);

		/* Finds if it's the end of a sentence */
        if(car==46 || car==33 || car==63){ //if character is '.' or '!' or '?'

            fprintf(dest,"%c",car);//write the character
            tmp1=fgetc(text); //tmp1=character after car

            if(tmp1==32 || tmp1==13 || tmp1==10){ //if == ' ' or Carriage return or Line Feed
                fprintf(dest,"</p>");//we consider that this was a sentence, so we put a closing tag
                fprintf(dest,"%c",tmp1);//write the char
                fprintf(dest,"<p>");//put the opening tag for the next sentence
            }
			
			/* To avoid writting the EOF char */
            else if(tmp1==EOF){//if we are at the end of the file
			
               fprintf(dest,"</p>");//write the final tag
            }
			
			/* If nothing of interest is read, then consider we're in 
			the middle of a sentence, and just write the char as is */
            else{
                fprintf(dest,"%c",tmp1); 
            }
        }
		
		/* This takes care of Carriage return and Line Feed */
        else if(car==13 || car==10){//if the read char is a Carriage return or a Line Feed

            tmp2=fgetc(text); //tmp2 = the character that comes after the currently read char (i.e 'car')
			
			/* if the char in the next line is a capital letter, then the sentence is over */
            if(tmp2>=65 && tmp2<=90){
                fprintf(dest,"</p>")//so we put the end tag, etc...
                fprintf(dest,"%c",car);
                fprintf(dest,"<p>");
                fprintf(dest,"%c",tmp2);
            }

			/* else if the char in the next line is a Carriage return or a Line Feed again, then the sentence is over */
            else if(tmp2==13 || tmp2==10){
                fprintf(dest,"</p>");
                fprintf(dest,"%c",car);
                fprintf(dest,"%c",tmp2);
                fprintf(dest,"<p>");
            }

			/* Otherwise, it was a simple carrige/Line Feed in the middle of a sentence, so keep writting the text */
            else{
                fprintf(dest,"%c",car);
                fprintf(dest,"%c",tmp2);
            }
        }
		
		/* If none of the above apply, then just keep writing the characters */
        else{
            fprintf(dest,"%c",car);
        }

    }while(car!= EOF);

    fclose(text);
    fclose(dest);

    return 0;
}
