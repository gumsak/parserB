#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int nbcar;
    int i=0;

    FILE* text = NULL;
    text = fopen("descartes.txt", "r");//A modifier selon le nom du texte à traiter
    FILE* dest = NULL;
    dest = fopen("dest.xml","w+");//Indiquer le nom et le type de fichier qu'on veut générer

//////////////CONNAITRE LE NBR DE CARACATERES DANS LA SOURCE - PAS UTILE/////////////
    do{
    nbcar = fgetc(text);
     i+=1;
        } while (nbcar != EOF);

    rewind(text);
    printf("Le texte original contient %d caracteres.\n",i );
///////////////********************************************************/////////////

    int car;
    int tmp1, tmp2;

    fprintf(dest,"<p>");//balise debut de texte

    do{
        car=fgetc(text);

// Condition pour fin de phrase

        if(car==46 || car==33 || car==63){ //si caractere == . || ! || ?

            fprintf(dest,"%c",car);//ecrire ce caractere
            tmp1=fgetc(text); //tmp1=caractere present apres car

            if(tmp1==32 || tmp1==13 || tmp1==10){ //si == ' ' || retour chariot || saut de ligne
                fprintf(dest,"</p>");
                fprintf(dest,"%c",tmp1);//ecrire le caractere
                fprintf(dest,"<p>");//considerer que c'est la fin de phrase
            }
//Pour eviter d'ecrire le EOF
            else if(tmp1==EOF){//on est a la fin du fichier

               fprintf(dest,"</p>");//balise finale
            }
//Si rien de specifique
            else{//sinon on continu d'ecrire normalement la phrase

                fprintf(dest,"%c",tmp1); //ecrire caractere dans dest
            }
        }
//Pour gerer les sauts de lignes/retours chariot
        else if(car==13 || car==10){//si car == retour chariot || saut de ligne

            tmp2=fgetc(text); //tmp2=caractere present apres car

            if(tmp2>=65 && tmp2<=90){//si MAJ a la ligne, alors fin de phrase
                fprintf(dest,"</p>");
                fprintf(dest,"%c",car);
                fprintf(dest,"<p>");
                fprintf(dest,"%c",tmp2);

            }

            else if(tmp2==13 || tmp2==10){//si encore retour chariot || saut de ligne, alors fin de phrase
                fprintf(dest,"</p>");
                fprintf(dest,"%c",car);

                fprintf(dest,"%c",tmp2);
                fprintf(dest,"<p>");
            }

            else{//sinon si simple saut de ligne mais pas fin de phrase
                fprintf(dest,"%c",car);
                fprintf(dest,"%c",tmp2); //ecrire caractere dans dest
            }
        }

        else{//sinon simplement ecrire le caractere
            fprintf(dest,"%c",car); //ecrire caractere dans dest
        }

    }while(car!= EOF);

    fclose(text);
    fclose(dest);

    return 0;
}
