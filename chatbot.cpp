#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<unistd.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<fstream>
#include<sstream>

using namespace std ;

//int a;

//class Server{
int flag=0 ;
char d[256] ;
int b ;
int c;
int opt ;
string e ;
string ans ;
//public:
typedef struct {
	char *input;
	char *responses;
}re;
int a ;

re KnowledgeBase[]={
	{"NAME",
	"MY NAME IS CHATBOT"
        },
        {"MORNING",
	"GOOD MORNING"
	},
	{"FOOD",
	 "www.foodpanda.com"
        },
	{"WEB SERIES PLATFORM",
	 "Netflix, Amazon Prime, Hotstar"
        },
	{"OHH NICE",
	 "Thank you!!!"
        },
	{"HELLO",
	 "Hello...I am your chatbot"
        },
	{"OK OKK THANKS",
	 "Your Welcome" 
        },
	{"GAMES",
	"Pub-g, Among us, 8-Ball Pool"
	},
	{"HII",
	"Hello"
	},
	{"TATA GOOD BYE GOODBYE",
	"Good Bye...nice talking with u"
	},
	{"HOW ARE YOU",
	"I am fine sir"
	},
	{"DO",
	"I can help you out with your queries to the best of my Knowledge"
        }


};

size_t nKnowledgeBaseSize = sizeof(KnowledgeBase)/sizeof(KnowledgeBase[0]);
void uppercase(string &str)
{
	int len = str.length();
	for( int i = 0; i < len; i++ ) 
	{
		if ( str[i] >= 'a' && str[i] <= 'z' ) 
		  {
		     str[i] -= 'a' - 'A';
		  }
	}
}

string findmatch(string k)
{
	flag=0 ;
	string nt="Sorry i didn't get what u said" ;
	string qt="Sorry I won't repeat" ;
	string prevResponse="zero" ;
	string gword ;
	string sword ;
	for(int i = 0; i < nKnowledgeBaseSize; ++i){

		   string keyWord(KnowledgeBase[i].input);
		  // stringstream s(k) ;
		   stringstream p(keyWord) ;
                   string word ;
		   string mm ;
                    while(p >> mm){
                                        stringstream s(k) ;
			                while(s >> word){
				        if(!word.compare(mm)){	
				        string result(KnowledgeBase[i].responses) ;
				//	stringstream r(result) ;
					stringstream p(prevResponse) ;
				//	string qt(KnowledgeBase[i].input) ;
					stringstream r(keyWord) ;

					while( (r >> gword) && (p >> sword) ){
				      
						
						if(sword.compare(gword)){
							prevResponse.clear() ;
						for(int j=0;j<keyWord.length();j++)
							prevResponse.push_back(keyWord[j]) ;
						        cout<<prevResponse<<"\n" ;
						flag=1 ;
						
						}
					
					}	
						
					        return result ;
						result.clear() ;

							break ;
					
		
					}	

                                       
			
					}
		    }
		    }
	return nt ;
}

void Server(char *argv[])
{
        opt=1 ;
        a = socket(AF_INET, SOCK_STREAM, 0) ;
        struct sockaddr_in mghaddress;

        if(setsockopt(a, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
        perror("setsockopt error");
        exit(1);
        }
        mghaddress.sin_family = AF_INET ;
        mghaddress.sin_port = htons(atoi(argv[2])) ;
//      mghaddress.sin_addr.s_addr = INADDR_ANY ;
        mghaddress.sin_addr.s_addr = inet_addr(argv[1]) ;
        int addrlen = sizeof(mghaddress) ;
        int b ;
        b = bind(a, (struct sockaddr *)&mghaddress, sizeof(mghaddress));

        if(b<0){
        perror("ERROR on binding\n") ;
        exit(1) ;
        }
        listen(a, 5) ;
//        c=accept(a, 0, 0) ;
        c=accept(a, (struct sockaddr *)&mghaddress,(socklen_t*)&addrlen) ;
        if(c < 0){
        perror("ERROR on accept\n") ;
        exit(1) ;
        }
}


void receivemsg()
{
        
        bzero(d,256) ;
        recv(c, d, sizeof(d), 0) ;
        if( (!bcmp(d, "quit", 4)) || (strlen(d)==0) ) {


        cout<<"\nConnection terminated" ;
        exit(1) ;
        }
        for(int k=0;k<strlen(d);k++)
		e.push_back(d[k]) ;
//        cout<<"\nMessage received from client: "<<d ;
	uppercase(e) ;
	ans=findmatch(e) ;
	send(c, ans.c_str(), strlen(ans.c_str()), 0) ;
	ans.clear() ;
	e.clear() ;
}


int main(int argc, char *argv[]){

        if(argc < 3 ){
        cout<<"Error.....Give port number as argument" ;
        exit(1) ;
        }



        Server(argv) ;
        while(1)
        {
        
        receivemsg() ;
       
        }

        return 0 ;
     }
