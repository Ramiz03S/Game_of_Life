#include <stdio.h>
#include <stdlib.h>

typedef struct cell { //this struct is to store information about each cell in the grid
    int alive_neighbors;
    int cell_status;
} cell;
typedef struct grid_type { // this struct is to store information about the entire grid
    int ncol;
    int nrow;
    cell **gridp;
} grid_type;

int print_howitworks (void);
int print_instructions (void);
int start_playing(void);

void print_menu (void){ //this function prints a list of options to the user to choose from at the beginning
    int n;
    printf("Welcome to Conways Game of life!\n");
    printf("1.How the game works\n") ;
    printf("2.Instructions\n");
    printf("3.Start playing!\n");
    scanf("%d",&n);
    switch (n) {
        case 1: system("cls");print_howitworks();break;
        case 2: system("cls");print_instructions();break;
        case 3: system("cls");start_playing();break;
        default: break;
    }
    return;
}
int print_howitworks (void){ //extracts a paragraph from a txt file to describe how the game works to the user
    char c;
    int n;
    FILE *fp;
    fp = fopen("How the game works.txt","r");
    if (fp == NULL)
        return 1;
    while (fscanf(fp,"%c",&c)== 1)
        printf("%c",c);
    fclose(fp);
    scanf("%d",&n);
    if (n=1){
        system("cls");
        print_menu();
    }
    return 0;
}
int print_instructions (void){ //extracts a paragraph from a txt file to tell the user how to play the game
    char c;
    int n;
    FILE *fp;
    fp = fopen("instructions.txt","r");
    if (fp == NULL)
        return 1;
    while (fscanf(fp,"%c",&c)== 1)
        printf("%c",c);
    fclose(fp);
    scanf("%d",&n);
    if (n=1){
        system("cls");
        print_menu();
    }
    return 0;
}
void init_grid(cell** grid,int nrow, int ncol){ //initializes all cells with a status of 0
    int i,j;
    for(i=0;i<nrow;i++){
        for(j=0;j<ncol;j++){//nested for loops to run through the cells of the grid
            grid[i][j].cell_status=0;
        }
    }
}
cell ** create_grid(int nrow, int ncol){ //allocates memory to create a grid with nrow number of rows and ncol number of columns
    int i;
    cell**grid=(cell**)malloc(nrow*sizeof(cell*));
    *grid=(cell*)malloc(nrow*ncol*sizeof(cell));
    for(i=1; i<nrow;++i){
        *(grid+i)=*(grid+i-1)+ncol;
    }
    return grid;
}
void print_grid(cell **grid,int nrow,int ncol){ //prints the grid to the screen
    int row,col;
    for(row=0;row<nrow;row++){
        for(col=0;col<ncol;col++){
            if(grid[row][col].cell_status==1){
                printf("((%d))",grid[row][col].cell_status);
            }
            else printf("  %d  ",grid[row][col].cell_status);

            if (col==ncol-1){printf("\n");}//to print a new line when the end of the column is reached
        }
    }
}
void save_to_file(cell **grid, int nrow, int ncol,FILE *fp){
    int i,j;
    for(i=0;i<nrow;i++){
        for(j=0;j<ncol;j++){
            if (grid[i][j].cell_status==1){
                fprintf(fp,"%d,%d\n",i,j);
            }
        }
    }
}
int num_live_neighbors (cell **grid,int nrow,int ncol,int i,int j){ //calculates the number of alive neighbors each cell has
    int counter=0,k;
    if(i>0 && i<nrow-1){ //this part is for non-edge cells
        if(j>0 && j<ncol-1){
            for(k=j-1;k<j+2;k++){
                if(grid[i-1][k].cell_status==1){
                    counter=counter+1;
                }
                if(grid[i+1][k].cell_status==1){
                    counter=counter+1;
                }
            }
            if(grid[i][j-1].cell_status==1){
                counter=counter+1;
            }
            if(grid[i][j+1].cell_status==1){
                counter=counter+1;
            }
        }
    }
    if(j+1==ncol && i!=0 && i!=nrow-1){ //cells on right edge but not corner cells
        for(k=j-1;k<j+1;k++){
            if(grid[i-1][k].cell_status==1){
                counter=counter+1;
            }
            if(grid[i+1][k].cell_status==1){
                counter=counter+1;
            }

            }
        if(grid[i-1][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][0].cell_status==1){
            counter=counter+1;
        }

        if(grid[i][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][j-1].cell_status==1){
            counter=counter+1;
        }
    }
    if(j-1<0 && i!=0 && i!=nrow-1){//cells of left edge but not corners
        for(k=j;k<j+2;k++){
            if(grid[i-1][k].cell_status==1){
                counter=counter+1;
            }
            if(grid[i+1][k].cell_status==1){
                counter=counter+1;
            }

        }
        if(grid[i-1][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][j+1].cell_status==1){//
            counter=counter+1;
        }
    }
    if(i-1<0 && j!=0 && j!=ncol-1){//top edge but not corners
        for(k=j-1;k<j+2;k++){
            if(grid[nrow-1][k].cell_status==1){
                counter=counter+1;
            }
            if(grid[i+1][k].cell_status==1){
                counter=counter+1;
            }
        }
        if(grid[i][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][j+1].cell_status==1){
            counter=counter+1;
        }
    }
    if(i+1==nrow && j!=0 && j!=ncol-1){//bottom edge but not corners
        for(k=j-1;k<j+2;k++){
            if(grid[i-1][k].cell_status==1){
                counter=counter+1;
            }
            if(grid[0][k].cell_status==1){
                counter=counter+1;
            }
        }
        if(grid[i][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][j+1].cell_status==1){
            counter=counter+1;
        }
    }
    if(i-1<0 && j-1<0){ //top-left corner cell
        if(grid[i][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][ncol-1].cell_status==1){
            counter=counter+1;
        }
    }
    if(i-1<0 && j+1==ncol){//top-right corner cell
        if(grid[i][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i+1][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[nrow-1][0].cell_status==1){
            counter=counter+1;
        }

    }
    if(i+1==nrow && j-1<0){//bottom-left corner cell
        if(grid[i][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][ncol-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][j+1].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][ncol-1].cell_status==1){
            counter=counter+1;
        }

    }
    if(i+1==nrow && j+1==ncol){//buttom-right corner cell
        if(grid[i][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[i-1][0].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][j].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][j-1].cell_status==1){
            counter=counter+1;
        }
        if(grid[0][0].cell_status==1){
            counter=counter+1;
        }
    }
    return counter;
}
void init_num_neighbors(cell **grid,int nrow,int ncol){ // stores the number of alive neighbors to the struct of each cell
    int i,j;
    for(i=0;i<nrow;i++){
        for(j=0;j<ncol;j++){
            grid[i][j].alive_neighbors=num_live_neighbors(grid,nrow,ncol,i,j);
        }
    }
}
void init_1_grid(cell **grid){ //asks the user to enter the coordinates of cells they want to be alive at the beginning
    int i,j;
    printf("enter the cell coordinates that you want to initialize with a value of 1(alive)\n");
    while((scanf("%d,%d\n",&i,&j))==2){
        grid[i][j].cell_status=1;
    }
}
cell **nextgrid(cell **grid, int nrow, int ncol){
    int i,j;
    cell **nextgrid=create_grid(nrow,ncol);//new grid to store the values of the next evolution
    for(i=0;i<nrow;i++){
        for(j=0;j<ncol;j++){//runs through the cells of the grid and applies the rules of conways game of life on them
            if(grid[i][j].alive_neighbors<2 && grid[i][j].cell_status==1){
                nextgrid[i][j].cell_status=0;
            }
            if(grid[i][j].cell_status==1 && grid[i][j].alive_neighbors>3){
                nextgrid[i][j].cell_status=0;
            }
            if(grid[i][j].cell_status==0 && grid[i][j].alive_neighbors==3){
                nextgrid[i][j].cell_status=1;
            }
            if(grid[i][j].cell_status==0 && grid[i][j].alive_neighbors!=3){
                nextgrid[i][j].cell_status=0;
            }
            if(grid[i][j].cell_status==1 && ((grid[i][j].alive_neighbors==3) || (grid[i][j].alive_neighbors==2))){
                nextgrid[i][j].cell_status=1;
            }
        }
    }
    free(grid[0]);
    free(grid);//freeing up the old grid
    return nextgrid;
}
int start_playing(void){
    grid_type grid;
    int c,n;
    printf("Do you want to enter cells manually(enter 1), or choose from pre-set configurations(enter 2)\n");
    scanf("%d",&c);
    if(c==1){//if user wants to enter cells manually
        system("cls");
        printf("Enter number of rows and columns of the grid you want(in X,X format)(greater than 3 by 3),or enter 0 to have a default 20,20 grid\n");
        scanf("%d,%d",&(grid.nrow),&(grid.ncol));
        if(grid.nrow<4 || grid.ncol<4){
            grid.nrow=20;
            grid.ncol=20;
        }
        grid.gridp=create_grid(grid.nrow,grid.ncol);
        init_grid(grid.gridp,grid.nrow,grid.ncol);
        system("cls");
        init_1_grid(grid.gridp);
        system("cls");
        init_num_neighbors(grid.gridp,grid.nrow,grid.ncol);
        print_grid(grid.gridp,grid.nrow,grid.ncol);
        printf("\n enter n to continue(where n is +ve int equal to the number of steps you want to take or 0 to return to menu or -1 to save grid\n");
        while(scanf("%d",&c)==1){
            if(c!=0 || c!=(-1)){
                for(n=0;n<c;n++){
                    grid.gridp=nextgrid(grid.gridp,grid.nrow,grid.ncol);
                    init_num_neighbors(grid.gridp,grid.nrow,grid.ncol);
                    system("cls");
                    print_grid(grid.gridp,grid.nrow,grid.ncol);
                    printf("\n enter n to continue(where n is +ve int equal to the number of steps you want to take or 0 to return to menu or -1 to save grid\n");
                }
            }

            if(c==0){
                free(grid.gridp[0]);
                free(grid.gridp);
                system("cls");
                print_menu();
            }
            if(c==-1){
                FILE *fp=fopen("new.file.txt","w");
                if(fp==NULL){
                    return -1;
                }
                save_to_file(grid.gridp,grid.nrow,grid.ncol,fp);
                fclose(fp);
            }
        }
    }
    if(c==2){//if user wants to choose from pre-set configurations
        char x;
        int n,d1,d2;
        system("cls");
        FILE *fp;
        fp = fopen("set_grids.txt","r"); //prints text to user to choose options from a list
        if (fp == NULL)
            return 1;
        while (fscanf(fp,"%c",&x)== 1)
            printf("%c",x);
        fclose(fp);
        grid.nrow=20;
        grid.ncol=20;
        grid.gridp=create_grid(grid.nrow,grid.ncol); //creates the grid of cells
        init_grid(grid.gridp,grid.nrow,grid.ncol);
        scanf("%d",&n); //user chooses one of the options and the alive cells get scanned from the related text file
        if (n==1){
            fp = fopen("LWSS.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if (n==2){
            fp = fopen("toad.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if (n==3){
            fp = fopen("glider.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if (n==4){
            fp = fopen("bunnies.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if (n==5){
            fp = fopen("bee_worker.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if (n==6){
            fp = fopen("new.file.txt","r");
            if (fp == NULL)
                return 1;
            while (fscanf(fp,"%d,%d",&d1,&d2)== 2){
                grid.gridp[d1][d2].cell_status=1;
            }
            fclose(fp);
        }
        if(n==1 ||n==2 ||n==3 ||n==4 ||n==5 || n==6){
        //starts the process of initiating the neighbors and displaying the grid
        init_num_neighbors(grid.gridp,grid.nrow,grid.ncol);system("cls");
            print_grid(grid.gridp,grid.nrow,grid.ncol);
            printf("\n enter n to continue(where n is +ve int equal to the number of steps you want to take or 0 to return to menu or -1 to save grid\n");
            while(scanf("%d",&c)==1){
            if(c!=0 || c!=(-1)){
                for(n=0;n<c;n++){
                    grid.gridp=nextgrid(grid.gridp,grid.nrow,grid.ncol);
                    init_num_neighbors(grid.gridp,grid.nrow,grid.ncol);
                    system("cls");
                    print_grid(grid.gridp,grid.nrow,grid.ncol);
                    printf("\n enter n to continue(where n is +ve int equal to the number of steps you want to take or 0 to return to menu or -1 to save grid\n");
                }
            }

            if(c==0){
                free(grid.gridp[0]);
                free(grid.gridp);
                system("cls");
                print_menu();
            }
            if(c==-1){
                FILE *fp=fopen("new.file.txt","w");
                if(fp==NULL){
                    return -1;
                }
                save_to_file(grid.gridp,grid.nrow,grid.ncol,fp);
                fclose(fp);
            }
        }
        }
        if (n==7){//lets user return to the main menu
            system("cls");
            print_menu();
        }
    }
    return 0;
}
int main(){
    print_menu();
    return 0;
}
