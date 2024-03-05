
#include "define.h"
#include "autotests.h"
#include "ams.h"
#include "amp.h"
#include "frame.h"
#define AMP_NB_TESTS 6


// fonction de base pour afficher les résultats de tests
void printAutoTestsResults(char* testName,int mark[],int coeff[],int nTests){
	int i=0;
	int cpt=0;
	int max=0;
	printf("---- Autotest results of block %s ----\n",testName);
	for(i=0;i<nTests;i++){
		printf("--> test %d : %d/%d\n",i,mark[i]*coeff[i],coeff[i]);
		cpt+=mark[i]*coeff[i];
		max +=coeff[i];
	}
	printf("Finish autotest of block %s => total score : %.1f %%\n",testName,(float)cpt/((float)max)*100);

}

void testReadAMS(){

	s_song mySong;
	int flag=0;
	int mark[2]={0,0};
	int coeff[2]={1,1};
	int i=0;
	int k=0;
	int cpt=0;
	int tpm;
	int accent;
	int nTicks;
	int note[4];
	char title[MAX_SIZE_TITLE];
	FILE* pf;
	
	// Test 1 : vérifier que la fonction renvoie une structure song vide quand le fichier ams n'existe pas
	mySong = readAMS(".ams");
	
	if (mySong.tpm==0 && strcmp(mySong.title,"")==0){
		for(i=0;i<MAX_NUMBER_TICKS;i++){
			if(mySong.tickTab[i].accent==0){
				for(k=0;k<4;k++){
					if(mySong.tickTab[i].note[k]==0){
						cpt++;
					}
				}
			}

		}
	}

	
	if(cpt==4*MAX_NUMBER_TICKS){
		mark[0]=1;
	}else{
		mark[0]=0;
	}


	// Test 2
	cpt=0;
	mySong = readAMS("bohemian_rhapsody.ams");
	pf = fopen("bohemian_rhapsody.ref","r");
	if(pf!=NULL){
		fgets(title,MAX_SIZE_TITLE,pf);
		title[strlen(title)-1]='\0';
		fscanf(pf,"%d",&tpm);
		//printf("%s %d",title,tpm);
		if(strcmp(title,mySong.title)==0){
			cpt++;
		}
		if(tpm==mySong.tpm){
			cpt++;
		}
		i=0;

		for(i=0;i<mySong.nTicks;i++){
			fscanf(pf,"%d\t %d\t %d\t %d\t %d\n",&accent,&note[0],&note[1],&note[2],&note[3]);
			//printf("%d\t %d\t %d\t %d\t %d",accent,note[0],note[1],note[2],note[3]);
			//getchar();
			if(mySong.tickTab[i].accent==accent){
				for(k=0;k<4;k++){
					if(mySong.tickTab[i].note[k]==note[k]){
						cpt++;
					}
				}
			}
		}
		fscanf(pf,"%d",&nTicks);
		if(mySong.nTicks==nTicks){
			cpt++;
		}


		fclose(pf);

	}
	if(cpt==(3+mySong.nTicks*4)){
		mark[1]=1;
	}else{
		mark[1]=0;
	}

	printAutoTestsResults("ReadAMS",mark,coeff,2);



}

void testReadAMP(){
    int cpt=0;
    int i=0;
    int nbtest = 0;
    int mark[AMP_NB_TESTS]={0};
    int coeff[AMP_NB_TESTS];
    for(i=0;i<AMP_NB_TESTS;i++){
    	coeff[i]=1;
    }
    int testnb = 0; // numéro du test en cours;
    char filename[100]="Playlist.amp";
    char wrongfile[100]="dtfhesjs.ams";

    // TEST 1 : on verifie que le pointeur est NULL si le fichier amp n'existe pas
    FILE * pf = initAMP(wrongfile);
    if (pf ==NULL){
        mark[nbtest] =1; // premier test de fichier vide passé
        #ifdef DEBUG
        printf("test %d AMP ok\n", nbtest);
        #endif
    }

    nbtest ++;
    cpt = 0;

    // TEST 2 : on verifie que le fichier Playlist.amp s'ouvre bien
    pf = initAMP(filename);
    if (pf != NULL){
        mark[nbtest]=1;
        #ifdef DEBUG
        printf("test %d AMP ok\n", nbtest);
        #endif
    }
    char songfilename[MAX_SIZE_TITLE];
    int songnumber = 0;
    while(!feof(pf)){ // read amp file line by line
        readAMP(pf, songfilename);
        nbtest ++;
        if (!strcmp("bohemian_rhapsody.ams", songfilename) && nbtest == 2){
            mark[nbtest]=1;
            #ifdef DEBUG
            printf("test %d AMP ok\n", nbtest);
            #endif
        }
        if (!strcmp("knockin_on_heaven_s_door.ams", songfilename) && nbtest == 3){
            mark[nbtest]=1;
            #ifdef DEBUG
            printf("test %d AMP ok\n", nbtest);
            #endif
        }
		if (!strcmp("clocks.ams", songfilename) && nbtest == 4){
            mark[nbtest]=1;
            #ifdef DEBUG
            printf("test %d AMP ok\n", nbtest);
            #endif
        }
        if (!strcmp("imagine.ams", songfilename) && nbtest == 5){
            mark[nbtest]=1;
            #ifdef DEBUG
            printf("test %d AMP ok\n", nbtest);
            #endif
        }

        printf("%s\n", songfilename);

    }

    printAutoTestsResults("ReadAMP",mark,coeff,AMP_NB_TESTS);

}


void testFrame() {
    int flag=0;
    int mark[4]={0};
    int coeff[4]={1,1,1,1};
    char initFrame[INIT_FRAME_MAX_SIZE];
    char tickFrame[TICK_FRAME_SIZE];
    s_tick myTick;

    // INIT FRAMERef[]
    char initFrameRef1[INIT_FRAME_MAX_SIZE];
    char initFrameRef2[INIT_FRAME_MAX_SIZE];
    char tickFrameRef1[TICK_FRAME_SIZE];
    char tickFrameRef2[TICK_FRAME_SIZE]; 
    sprintf(initFrameRef1,"#Bohemian Rhapsody,144,16*17\r\n");
    sprintf(initFrameRef2,"#Buhemian Rhapsody,144,16*0d\r\n");
    sprintf(tickFrameRef1,"#0,1,11,23,27,34*2e\r\n");
    sprintf(tickFrameRef2,"#0,1,11,18,00,00*24\r\n");
  
    s_song mySong;
    // Bohemian Rhapsody, test simple
    mySong.tpm = 144;
    mySong.nTicks = 16;
    strncpy(mySong.title, "Bohemian Rhapsody", MAX_SIZE_TITLE);
    createInitFrame(mySong, initFrame);
    //printf("initFrame=%s\n",initFrame);
    //printf("initFrameRef=%s\n",initFrameRef);

    if(strcmp(initFrame,initFrameRef1)==0){
    	mark[0]=1;
    }else{
    	mark[0]=0;
    }

    // Bohemian Rhapsody, test sur le 0 padding du checksum
    mySong.tpm = 144;
    mySong.nTicks = 16;
    strncpy(mySong.title, "Buhemian Rhapsody", MAX_SIZE_TITLE);
    createInitFrame(mySong, initFrame);
    //printf("initFrame=%s\n",initFrame);
    //printf("initFrameRef=%s\n",initFrameRef);

    if(strcmp(initFrame,initFrameRef2)==0){
    	mark[1]=1;
    }else{
    	mark[1]=0;
    }


    // TICK FRAME 1
    myTick.accent = 1;
    myTick.note[0]=11;
    myTick.note[1]=23;
    myTick.note[2]=27;
    myTick.note[3]=34;
    createTickFrame(myTick, tickFrame);
     if(strcmp(tickFrame,tickFrameRef1)==0){
    	mark[2]=1;
    }else{
    	mark[2]=0;
    }

    // TICK FRAME 2
    myTick.accent = 1;
    myTick.note[0]=11;
    myTick.note[1]=18;
    myTick.note[2]=00;
    myTick.note[3]=00;
    createTickFrame(myTick, tickFrame);
     if(strcmp(tickFrame,tickFrameRef2)==0){
    	mark[3]=1;
    }else{
    	mark[3]=0;
    }

    printAutoTestsResults("Frame",mark,coeff,4);



}

void testCreateAMS(){
	FILE* pf1=NULL;
	FILE* pf2=NULL;
	int nCorrectLines= 0;
	int nLines=0;
	char buffer[MAX_SIZE_LINE];
	char buffer_ref[MAX_SIZE_LINE];
	int mark[2]={0};
	int coeff[2]={1,9};
	char txtFileName[] = "bohemian_rhapsody.txt";
	char amsFileName[] = "test.ams";
	char refFileName[] = "bohemian_rhapsody.ams";
	createAMS(txtFileName,amsFileName);

	pf1=fopen(amsFileName,"r");
	if(pf1==NULL){
		mark[0]=0;
	}else{
		mark[0]=1;
	}
	pf2 = fopen(refFileName,"r");
	if(pf2==NULL){
		printf("in testCreateAMS, ref file name cannot be opened!\n");
	}

	if(pf1!=NULL && pf2!=NULL){
		while(!feof(pf2)){
			fgets(buffer_ref,MAX_SIZE_LINE,pf2);
			nLines++;
			if(!feof(pf1)){
				fgets(buffer,MAX_SIZE_LINE,pf1);
				if(strcmp(buffer,buffer_ref)==0){
					nCorrectLines+=1;
				}
			}
		}
		if(nLines==nCorrectLines){
			mark[1]=1;
		}else{
			mark[1]=0;
		}

	}
   printAutoTestsResults("CreateAMS",mark,coeff,2);

}