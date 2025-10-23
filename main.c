#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//caracteristicile unui autoturism
typedef struct {
    char marca[50];
    char tip[50];
    int locuri;
    float consumCombustibil;
    char culoare[20];
    int disponibil;
    char dataRezervare[20];
} Autoturism;

// Functie care intoarce codul de culoare ANSI in functie de numele culorii
const char* cod_culoare(const char* culoare) {
    if (strcmp(culoare, "rosu") == 0) return "\033[38;5;196m";       // roșu aprins
    if (strcmp(culoare, "portocaliu") == 0) return "\033[38;5;208m"; // portocaliu
    if (strcmp(culoare, "galben") == 0) return "\033[38;5;226m";     // galben intens
    if (strcmp(culoare, "verde") == 0) return "\033[38;5;46m";       // verde viu
    if (strcmp(culoare, "albastru") == 0) return "\033[38;5;21m";    // albastru închis
    if (strcmp(culoare, "indigo") == 0) return "\033[38;5;54m";      // indigo
    if (strcmp(culoare, "mov") == 0) return "\033[38;5;201m";     //mov
    if  (strcmp(culoare,"roz")==0) return "\033[38;2;255;182;193m";
    return "\033[0m"; // reset (culoare normală)
}

//Functie care verifica daca data este corecta
int verificare_data(char *s) {
    int zi, luna, an;
    if (strlen(s)!= 10){
        return 0;
    }

    if (s[2]!= '.' || s[5]!= '.'){
        return 0;
    }
    zi = (s[0]-'0')*10 + (s[1] -'0');
    luna = (s[3]-'0')*10 + (s[4]-'0');
    an = (s[6]-'0')*1000 + (s[7]-'0')*100 + (s[8]-'0')*10 + (s[9]-'0');

    if (luna<1 || luna>12){
        return 0;
    }
    if (zi<1 || zi>31) {
        return 0;
    }

    if (an<2024 || an>2028){
        return 0;
    }

    if ((luna==4 || luna==6 || luna==9 || luna==11) && zi>30){
        return 0;
    }
    if (luna==2){
        if ((an%4==0&&zi>29) || (an%4!=0 && zi>28)) {
            return 0;
        }
    }

    return 1;
}

void only_letters(char culoare[])
{
    int ok=0;
    do
    {
       scanf("%s",culoare);
       int len=strlen(culoare);
       for(int i=0;i<len;i++)
       {
           if(culoare[i]<'a' || culoare[i]>'z')
           {
               ok=0;
               break;
           }
           ok=1;
       }
       if(ok==0)
          printf("Numele culorii trebuie sa contina doar litere mici. Reintroduceti: ");
    }while(ok==0);
}

void positive_numbers(int *numar_locuri)
{
    do
    {
       scanf("%d",numar_locuri);
       if(*numar_locuri<1)
       {
          printf("Numarul de locuri nu poate sa fie mai mic decat unu. Reintroduceti: ");
       }
    }while(*numar_locuri<1);
}

//Functie care anuleaza o rezervare a unui autotutrism
void anuleaza_rez(Autoturism autoturisme[],int* n){
    int ok=0;
    char marca[50],tip[50],culoare[20],dataRezervare[20];
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    printf("Introduceti data in care ati facut rezervarea(DD.MM.YYYY):");
    scanf("%s",dataRezervare);

    ok=0;
    int ver=verificare_data(dataRezervare);
    for(int i=0;i<*n;++i)
    {
        if(ver==0)
        {
            ok=1;
            printf("Data rezervarii nu este corecta!\n");
            break;
        }
        else
        {
         if(strcmp(autoturisme[i].marca,marca)==0 &&
            strcmp(autoturisme[i].culoare,culoare)==0 &&
            strcmp(autoturisme[i].tip,tip)==0)
            {
                if(strcmp(autoturisme[i].dataRezervare,dataRezervare)==0)
                {
                    strcpy(autoturisme[i].dataRezervare,"N/A");
                    ok=1;
                    autoturisme[i].disponibil=0;
                    printf("Rezervarea pe data %s a fost anulata",dataRezervare);
                    break;
                }
                else
                {
                   ok=1;
                   printf("Nu exista rezervare la aceasta data!\n");
                   break;
                }
            }
        }

    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care creaza o rezervare pentru un autoturism
void rezerva_auto(Autoturism autoturisme[],int* n){
    char marca[50],tip[50],culoare[20],dataRezervare[20];
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    printf("Introduceti data in care doriti rezervarea(DD.MM.YYYY):");
    scanf("%s",dataRezervare);
    int ok=0;
    int ver=verificare_data(dataRezervare);
    for(int i=0;i<*n;++i)
    {
        if(ver==0)
        {
            ok=0;
            printf("Data rezervarii nu este corecta!\n");
            break;
        }
        else
            if(strcmp(autoturisme[i].marca,marca)==0 &&
               strcmp(autoturisme[i].tip,tip)==0 &&
               strcmp(autoturisme[i].culoare,culoare)==0)
               if(autoturisme[i].disponibil==0)
                {
                    strcpy(autoturisme[i].dataRezervare,dataRezervare);
                    ok=1;
                    autoturisme[i].disponibil=1;
                    printf("Rezervarea pe data %s a fost facuta",dataRezervare);
                    break;
                }
                else
                {
                    ok=1;
                    printf("Masina este deja rezervata!");
                    break;
                }
    }

    if(ok==0)
       printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care afiseaza autoturismele care au o anumita marca si o anumita culoare
void marca_culoare_auto(Autoturism autoturisme[],int* n){
    char culoare[50],marca[50];
    int ok=0;
    printf("Introduceti culoarea cautata: ");
    only_letters(culoare);
    printf("Introduceti marca cautat: ");
    scanf("%s",marca);
    for(int i=0;i<*n;++i)
        {
        if(strcmp(culoare,autoturisme[i].culoare)==0 && strcmp(marca,autoturisme[i].marca)==0)
            {
                printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
                printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
                printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
                printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
                printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
                printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
                printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
                printf("/-----------------/\n");
                printf("\n");
                ok=1;

            }
       }
      if(ok==0){
            printf("Nu exista acesta culoare sau aceasta marca!\n");
        }
}

//Functie care afiseaza autoturismele care au o anumita marca si un anumit tip
void marca_tip_auto(Autoturism autoturisme[],int* n){
    char tip[50],marca[50];
    int ok=0;
    printf("Introduceti tipul cautat: ");
    scanf("%s",tip);
    printf("Introduceti marca cautat: ");
    scanf("%s",marca);
    for(int i=0;i<*n;++i)
        {
        if(strcmp(tip,autoturisme[i].tip)==0 && strcmp(marca,autoturisme[i].marca)==0)
            {
            printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
            printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
            printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
            printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
            printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
            printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
            printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
            printf("/-----------------/\n");
            printf("\n");
            ok=1;

            }
       }
      if(ok==0){
            printf("Nu exista acest tip sau aceasta marca!\n");
        }
}


//Functie care afiseaza autoturismele care au un anumit tip
void tip_auto(Autoturism autoturisme[],int* n){
    char tip[50];
    int ok=0;
    printf("Introduceti tipul cautat: ");
    scanf("%s",tip);
    for(int i=0;i<*n;++i)
        {
        if(strcmp(tip,autoturisme[i].tip)==0)
            {
                printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
                printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
                printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
                printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
                printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
                printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
                printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
                printf("/-----------------/\n");
                printf("\n");
                ok=1;

            }
       }
      if(ok==0){
            printf("Nu exista acest tip!\n");
        }
}

//Functie care afiseaza autoturismele care au un anumit numar de locuri
void nr_locuri_auto(Autoturism autoturisme[],int* n){
    int locuri;
    int ok=0;
    printf("Introduceti numarul de locuri cautat: ");
    positive_numbers(&locuri);
    for(int i=0;i<*n;++i)
        {
        if(locuri==autoturisme[i].locuri)
            {
                printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
                printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
                printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
                printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
                printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
                printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
                printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
                printf("/-----------------/\n");
                printf("\n");
                ok=1;

            }
       }
      if(ok==0){
            printf("Nu exista nici o masina cu acest numar de locuri!\n");
        }

}

//Functie care afiseaza autoturismele care au o anumita culoare
void culoare_auto(Autoturism autoturisme[],int* n){
    char culoare[20];
    int ok=0;
    printf("Introduceti culoarea cautata: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
        {
        if(strcmp(culoare,autoturisme[i].culoare)==0)
            {
                printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
                printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
                printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
                printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
                printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
                printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
                printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
                printf("/-----------------/\n");
                printf("\n");
                ok=1;
            }
       }
      if(ok==0){
            printf("Nu exista aceasta culoare!\n");
        }
}

//Functie care afiseaza autoturismele care au o anumita marca
void marca_auto(Autoturism autoturisme[],int* n){
    char marca[50];
    int ok=0;
    printf("Introduceti marca cautata: ");
    scanf("%s",marca);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(marca,autoturisme[i].marca)==0)
            {
                printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
                printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
                printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
                printf("Consum (100 L/KM): \033[35m%1.f\033[0m\n", autoturisme[i].consumCombustibil);
                printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
                printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
                printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
                printf("/-----------------/\n");
                printf("\n");
                ok=1;
            }
    }
    if(ok==0){
            printf("Nu exista aceasta marca auto!\n");
        }
}

//Functie care modifica tipul unui autoturism
void modif_tip(Autoturism autoturisme[],int* n){
    char marca[50],modftip[50],tip[50],culoare[20],dataRezervare[20];
    int ok=0;
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(autoturisme[i].marca,marca)==0 &&
           strcmp(autoturisme[i].tip,tip)==0 &&
           strcmp(autoturisme[i].culoare,culoare)==0)
           {
               printf("Introduceti noul tip: ");
               scanf("%s",modftip);
               strcpy(autoturisme[i].tip,modftip);
               ok=1;
               printf("Modificarea s-a facut cu succes!");
               break;
           }
    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care modifica consumul de combustibil unui autoturism
void modif_consum(Autoturism autoturisme[],int* n){
    char marca[50],tip[50],culoare[20],dataRezervare[20];
    int ok=0;
    float modfconsum;
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(autoturisme[i].marca,marca)==0 &&
           strcmp(autoturisme[i].tip,tip)==0 &&
           strcmp(autoturisme[i].culoare,culoare)==0)
           {
               printf("Introduceti noul consum de combustibil (N.N): ");
               scanf("%f",&modfconsum);
               autoturisme[i].consumCombustibil=modfconsum;
               ok=1;
               printf("Modificarea s-a facut cu succes!");
               break;
           }
    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care modifica numarul de locuri al  unui autoturism
void modif_nrloc(Autoturism autoturisme[],int* n){
    char marca[50],tip[50],culoare[20],dataRezervare[20];
    int ok=0,modfnrloc;
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(autoturisme[i].marca,marca)==0 &&
           strcmp(autoturisme[i].tip,tip)==0 &&
           strcmp(autoturisme[i].culoare,culoare)==0)
           {
               printf("Introduceti noul numar de locuri: ");
               positive_numbers(&modfnrloc);
               autoturisme[i].locuri=modfnrloc;
               ok=1;
               printf("Modificarea s-a facut cu succes!");
               break;
           }
    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care modifica culoarea unui autoturism
void modif_culoare(Autoturism autoturisme[],int* n){
    char marca[50],modfculoare[50],tip[50],culoare[20],dataRezervare[20];
    int ok=0;
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(autoturisme[i].marca,marca)==0 &&
           strcmp(autoturisme[i].tip,tip)==0 &&
           strcmp(autoturisme[i].culoare,culoare)==0)
           {
               printf("Introduceti noua culoare: ");
               only_letters(modfculoare);
               strcpy(autoturisme[i].culoare,modfculoare);
               ok=1;
               printf("Modificarea s-a facut cu succes!");
               break;
           }
    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care modifica marca unui autoturism
void modif_marca(Autoturism autoturisme[],int* n){
    char marca[50],modfmarca[50],tip[50],culoare[20],dataRezervare[20];
    int ok=0;
    printf("Introduceti marca autoturismului: ");
    scanf("%s",marca);
    printf("Introduceti tipul autoturismului: ");
    scanf("%s",tip);
    printf("Introduceti culoarea autoturismului: ");
    only_letters(culoare);
    for(int i=0;i<*n;++i)
    {
        if(strcmp(autoturisme[i].marca,marca)==0 &&
           strcmp(autoturisme[i].tip,tip)==0 &&
           strcmp(autoturisme[i].culoare,culoare)==0)
           {
               printf("Introduceti noua marca: ");
               scanf("%s",modfmarca);
               strcpy(autoturisme[i].marca,modfmarca);
               ok=1;
               printf("Modificarea s-a facut cu succes!");
               break;
           }
    }
    if(ok==0)
        printf("Masina nu exista!");
    salveaza_date(autoturisme,*n);
}

//Functie care sterge un autoturism
void sterge_autoturism(Autoturism autoturisme[], int* n) {
    char marca_sters[50], tip_sters[50];
    printf("Introduceti marca autoturismului pe care doriti sa il stergeti: ");
    scanf("%s", marca_sters);
    printf("Introduceti tipul autoturismului pe care doriti sa il stergeti: ");
    scanf("%s", tip_sters);

    int gasit=0;
    for (int i=0;i<*n;i++) {
        if (strcmp(autoturisme[i].marca, marca_sters) == 0 && strcmp(autoturisme[i].tip, tip_sters)==0)
        {
            for (int j=i;j<*n-1;j++)
                {
                autoturisme[j]=autoturisme[j+1];
            }
            (*n)--;
            gasit=1;
            printf("Autoturismul %s %s a fost sters cu succes!\n", marca_sters, tip_sters);
            break;
        }
    }

    if (!gasit) {
        printf("Autoturismul %s %s nu a fost gasit in lista.\n", marca_sters, tip_sters);
    }
    salveaza_date(autoturisme,*n);
}

//Functie care adauga un autoturism
void adauga_autoturism(Autoturism* autoturism) {
    printf("Introduceti marca: ");
    scanf("%s", autoturism->marca);
    printf("Introduceti tipul: ");
    scanf("%s", autoturism->tip);
    printf("Introduceti numarul de locuri: ");
    positive_numbers(&autoturism->locuri);
    printf("Introduceti consumul de combustibil (N.N): ");
    scanf("%f", &autoturism->consumCombustibil);
    printf("Introduceti culoarea: ");
    only_letters(autoturism->culoare);
    autoturism->disponibil = 0; // Inițial, mașina este disponibilă
    strcpy(autoturism->dataRezervare, "N/A"); // Data rezervării este inițial "N/A"
    printf("Autoturismul a fost adaugat cu succes!\n");

    // Salvare automată în fișier
    FILE *fptr = fopen("autoturisme.txt", "a"); // Deschide fișierul în mod append
    if (fptr == NULL) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }
    fprintf(fptr, "%s %s %d %.1f %s %d %s\n",
            autoturism->marca,
            autoturism->tip,
            autoturism->locuri,
            autoturism->consumCombustibil,
            autoturism->culoare,
            autoturism->disponibil,
            autoturism->dataRezervare);
    fclose(fptr);

}

//Functie care afiseaza toate autotutrismele
void afisare_auto(Autoturism autoturisme[], int n) {
    if (n == 0) {
        printf("Nu exista autoturisme\n");
    } else {
        printf("<---> Lista tuturor autoturismelor <--->\n");
        for (int i = 0; i < n; i++) {
            printf("Marca autoturism: \033[34m%s\033[0m\n", autoturisme[i].marca); // albastru
            printf("Tipul autoturism: \033[36m%s\033[0m\n", autoturisme[i].tip);
            printf("Numarul de locuri: \033[38;5;94m%d\033[0m\n", autoturisme[i].locuri);
            printf("Consum (100 L/KM): \033[35m%.1f\033[0m\n", autoturisme[i].consumCombustibil);
            printf("Culoare autoturism: %s%s\033[0m\n", cod_culoare(autoturisme[i].culoare), autoturisme[i].culoare); // culoare personalizată
            printf("Disponibilitate: \033[38;2;80;200;120m%s\033[0m\n", autoturisme[i].disponibil ? "Da" : "Nu");
            printf("Data rezervare: \033[90m%s\033[0m\n", autoturisme[i].dataRezervare);
            printf("/-----------------/\n");
            printf("\n");
        }
    }
}

//Functie de salvare a datelor
void salveaza_date(Autoturism autoturisme[], int n) {
    FILE *fptr;
    fptr = fopen("autoturisme.txt", "w");
    if (fptr == NULL) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fptr, "%s %s %d %.1f %s %d %s\n",
                autoturisme[i].marca,
                autoturisme[i].tip,
                autoturisme[i].locuri,
                autoturisme[i].consumCombustibil,
                autoturisme[i].culoare,
                autoturisme[i].disponibil,
                autoturisme[i].dataRezervare);
    }

    fclose(fptr);
    printf("\nDatele au fost salvate cu succes.\n");
}

//Functie de stocare a datelor
void stocare_date(Autoturism autoturisme[], int *n) {
    FILE *fptr;
    fptr = fopen("autoturisme.txt", "r");
    if (fptr == NULL) {
        printf("Fisierul nu exista sau este gol.\n");
        *n = 0;
        return;
    }

    *n = 0;
    while (fscanf(fptr, "%s %s %d %f %s %d %s",
                  autoturisme[*n].marca,
                  autoturisme[*n].tip,
                  &autoturisme[*n].locuri,
                  &autoturisme[*n].consumCombustibil,
                  autoturisme[*n].culoare,
                  &autoturisme[*n].disponibil,
                  autoturisme[*n].dataRezervare) != EOF) {
        (*n)++;
    }

    fclose(fptr);
}

//Meniul principal
void menu(){
    printf("## <-- Meniu --> ##\n");
    printf("1. <> Afiseaza toate autoturismele <>\n");
    printf("2. <> Adauga un nou autoturism <>\n");
    printf("3. <> Actualizeaza autoturism <>\n");
    printf("4. <> Sterge autoturism <>\n");
    printf("5. <> Cauta un anumit autoturism <>\n");
    printf("6. <> Rezerva un autoturism <>\n");
    printf("7. <> Anuleaza rezervarea <>\n");
    printf("8. <> Iesire <>\n");
}

//Meniu de cautare autoturism
void submenu(){
    printf("## <-- Cauta autoturism dupa -->##\n");
    printf("1. <> Marca masinii <>\n");
    printf("2. <> Culoarea masinii <>\n");
    printf("3. <> Numarul de locuri <>\n");
    printf("4. <> Tipul masinii <>\n");
    printf("5. <> Marca si tip <>\n");
    printf("6. <> Marca si culoare <>\n");
}

//Meniu de modificare autoturism
void submenu1(){
    printf("## <-- Modifica masina dupa -->##\n");
    printf("1. <> Marca masinii <>\n");
    printf("2. <> Culoarea masinii <>\n");
    printf("3. <> Numarul de locuri <>\n");
    printf("4. <> Tipul masinii <>\n");
    printf("5. <> Consuml de combustibil <>\n");
}

int main()
{  Autoturism autoturisme[100];
   int n=0,optiune;
   stocare_date(autoturisme,&n);
    do {
    menu();
    printf("Alegeti optiunea in functie de numarul corespunzator: ");
    scanf("%d",&optiune);
    system("cls");
    if(optiune==1){
        afisare_auto(autoturisme,n);
    }
    else if(optiune==2){
        if (n >= 100)
        {
        printf("Nu se mai pot adauga autoturisme. Limita de 100 a fost atinsa.\n");
        }
    else {
        printf("Adaugati un nou autoturism:\n");
        adauga_autoturism(&autoturisme[n]);
        n++;
        }
    }
    else if(optiune==3){
            submenu1();
            int varianta;
            printf("Alegeti optiunea in functie de numarul corespunzator: ");
            scanf("%d",&varianta);
            system("cls");
            if(varianta==1){
                modif_marca(autoturisme,&n);
            }
            else if(varianta==2){
                modif_culoare(autoturisme,&n);
            }
            else if(varianta==3){
                modif_nrloc(autoturisme,&n);
            }
            else if(varianta==4){
                modif_tip(autoturisme,&n);
            }
            else if(varianta==5){
                modif_consum(autoturisme,&n);
            }
            else{
                printf("Varianta aleasa este incorecta!");
            }
    }
    else if(optiune==4){
            sterge_autoturism(autoturisme,&n);
    }
    else if(optiune==5){
            submenu();
            int alegere;
            printf("Alegeti optiunea in functie de numarul corespunzator: ");
            scanf("%d",&alegere);
            system("cls");
            if(alegere==1){
                marca_auto(autoturisme,&n);
            }
            else if(alegere==2){
                culoare_auto(autoturisme,&n);
            }
            else if(alegere==3){
                nr_locuri_auto(autoturisme,&n);
            }
            else if(alegere==4){
                tip_auto(autoturisme,&n);
            }
            else if(alegere==5){
                marca_tip_auto(autoturisme,&n);
            }
            else if(alegere==6){
                marca_culoare_auto(autoturisme,&n);
            }
            else{
                printf("Varianta aleasa este incorecta!");
            }
    }
    else if(optiune==6){
            rezerva_auto(autoturisme,&n);
    }
    else if(optiune==7){
            anuleaza_rez(autoturisme,&n);
    }
    else if(optiune==8){
       printf("La revedere, o zi buna!\n");
       exit(1);
    }
    else{
        printf("Optiune invalida.Incercati din nou");
    }
        printf("\nApasati Enter pentru a continua...");
        while (getchar() != '\n');
        getchar();
        system("cls");
    } while (1);
    return 0;
}
