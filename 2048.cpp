#include <iostream>
#include <conio.h>
#include <cstdlib>

using namespace std;

class game_logic
{

    int grid[4][4],bgrid[4][4];
    int endgame;
    int response;
    int max;

        public:

        char moves;
        char option;
        string name;

        game_logic(): max(0),response(0),endgame(1) {}

        void startgrid();
        void display_grid();
        void fill_blank_space();
        void update_grid();
        void new_num();
        int full();
        void game_end_check(game_logic *);
        void greatest_block();
        void logic_flow(game_logic*);
        int changed_grid_check();
        void backup_grid();
        char try_again(int);
};




int main()
{
    game_logic exe;
    exe.startgrid();
    while(1)
    {
        exe.display_grid();
        cin>>exe.moves;
        exe.logic_flow(&exe);
        exe.game_end_check(&exe);
    };

    return 0;
}

void game_logic::startgrid()
{
    int i,j;

    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
        grid[i][j]=0;

    i=rand()%4;
    j=rand()%4;
    grid[i][j]=2;

    i=rand()%4;
    j=rand()%4;
    grid[i][j]=2;

}

void game_logic::display_grid()
{
        system("cls");

        cout<<"\t\t\t\t::The 2048 Game::\n\n\n";
        for(int i=0;i<4;i++)
		{
            cout<<"\n\t|";
			for(int j=0;j<4;j++)
			{
				if(grid[i][j])
				cout<<"\t"<<grid[i][j]<<"\t|";
                else
                cout<<"\t \t|";
			}

            cout<<endl<<endl;
        }

        cout<<"\n\n Controls:- \t\t\t\t\t\n\n\tW\t\t     ^\t\t\t\n"
		    <<" \n   A    S    D\t\t<    v    >\t\t\t     \n\n";

}

void game_logic::new_num()
{
		int i,j,k;

		do
		{
		    i=rand()%4;
		    j=rand()%4;
		    k=rand()%10;

		}while(grid[i][j]);



		if(k<2)
		    grid[i][j]=4;

		else
		    grid[i][j]=2;

}

void game_logic::fill_blank_space()
{

	switch(moves)
	{
		case 'w':
					for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
						{
							if(!grid[j][i])
							{
								for(int k=j+1;k<4;k++)
									if(grid[k][i])
									{
										grid[j][i]=grid[k][i];
										grid[k][i]=0;
										break;
									}
							}

						}break;

		case 's':
					for(int i=0;i<4;i++)
						for(int j=3;j>=0;j--)
						{
							if(!grid[j][i])
							{
								for(int k=j-1;k>=0;k--)
									if(grid[k][i])
									{
										grid[j][i]=grid[k][i];
										grid[k][i]=0;
										break;
									}
							}

						}break;
		case 'a':
					for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
						{
							if(!grid[i][j])
							{
								for(int k=j+1;k<4;k++)
									if(grid[i][k])
									{
										grid[i][j]=grid[i][k];
										grid[i][k]=0;
										break;
									}
							}

						}break;


		case 'd':
					for(int i=0;i<4;i++)
						for(int j=3;j>=0;j--)
						{
							if(!grid[i][j])
							{
								for(int k=j-1;k>=0;k--)
									if(grid[i][k])
									{
										grid[i][j]=grid[i][k];
										grid[i][k]=0;
										break;
									}
							}

						}break;

	}
}

void game_logic::update_grid()
{
    endgame=1;
    switch(moves)
	{
		case 'w':
					for(int i=0;i<4;i++)
						for(int j=0;j<3;j++)
						{
							if(grid[j][i]&&grid[j][i]==grid[j+1][i])
							{
								endgame=0;
								grid[j][i]+=grid[j+1][i];
								grid[j+1][i]=0;
							}
						}break;

		case 's':
					for(int i=0;i<4;i++)
						for(int j=3;j>0;j--)
						{
							if(grid[j][i]&&grid[j][i]==grid[j-1][i])
							{
								endgame=0;
								grid[j][i]+=grid[j-1][i];
								grid[j-1][i]=0;
							}
						}break;

		case 'a':
					for(int i=0;i<4;i++)
						for(int j=0;j<3;j++)
						{
							if(grid[i][j]&&grid[i][j]==grid[i][j+1])
							{
								endgame=0;
								grid[i][j]+=grid[i][j+1];
								grid[i][j+1]=0;
							}
						}break;

		case 'd':
					for(int i=0;i<4;i++)
						for(int j=3;j>0;j--)
						{
							if(grid[i][j]&&grid[i][j]==grid[i][j-1])
							{
								endgame=0;
								grid[i][j]+=grid[i][j-1];
								grid[i][j-1]=0;
							}
						}break;


	}

}

int game_logic::full()
{
	int f=1;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			if(!grid[i][j])
				f=0;

		}
return f;

}

void game_logic::logic_flow(game_logic *execute)
{

  switch(moves)
  {
      case 'w':

      case 'a':

      case 's':

      case 'd':

		  execute->backup_grid();
		  execute->fill_blank_space();
		  execute->update_grid();
		  execute->fill_blank_space();
		  execute->greatest_block();
		  execute->display_grid();

		  if(execute->full()&&endgame)
		  {
		      response=-1;
		      break;
		  }

		  else if(execute->changed_grid_check())
		  {
		      execute->new_num();
		      break;
		  }
		  else
            response=0;
            break;

  }
}



int game_logic::changed_grid_check()
{
	int b=0;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(bgrid[i][j]!=grid[i][j])
			{
				b=1;
				break;
			}
return b;

}


void game_logic::backup_grid()
{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				bgrid[i][j]=grid[i][j];

}

void game_logic::greatest_block()
{
    max=0;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(grid[i][j]>max)
				max=grid[i][j];

}

void game_logic::game_end_check(game_logic *screen)
{
  if(max==2048)
  {
    system("cls");

	cout<<endl<<endl;

	cout<<"\n\t\t\t  :: [  YOU MADE "<<"2048"<<"!  ] ::"
	    <<"\n\n\t\t\t  :: [ YOU WON THE GAME ] ::"
	    <<"\n\n\n\n\t\t\t MAX\t    NAME";

	cout<<"\n\n\t\t\t "<<max<<"\t    ";
	cin>>name;


  }

  else if(response==-1)
  {
    system("cls");

	cout<<"\n\n\n\t\t\t  :: [ G A M E  O V E R ] ::"
	    <<"\n\n\n\n\t\t\t MAX\t    NAME";
	cout<<"\n\n\t\t\t "<<max<<"\t    ";
	cin>>name;

    if(screen->try_again(1)=='y')
    {
	screen->startgrid();
	response=0;
    }

  }

  if(response==-1)
  {
    cout<<"\n\n\t\t            > Thank you for playing. "
        <<"\n\n\n   \n\n";

    getch();

    exit(0);

  }

}
char game_logic::try_again(int lose)
{

	if(lose)
	cout<<"\n\n\n\t    > Would you like to try again "<<name<<" (y/n) ? :: ";

	cin>>option;


return option;

}

//This Game has been made by Sushant, Sparsh And Prataya...!!!
