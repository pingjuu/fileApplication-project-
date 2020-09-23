#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <map>
#include "person.h"

std::map<unsigned int, struct person> database;                 //데이터 베이스를 관리하기 편하게 하기위해 map 자료구조 사용
                                                                //key : 학번 value : 학생 정보
void person_insert();
void person_delete();
void person_update();
void search();
void print(); 

int main(){
    int n=0;
    FILE *fp;                       //기존 파일 초기화
    fp = fopen("adr.dat", "w+");
    fclose(fp);

    while(n!=4){                
        std::cout<<"\n************메뉴를 고르시오 *************\n";
        std::cout<<"1.삽입\t2.삭제\t3.수정\t4.종료\t5.검색\n";
        std::cout<<"번호를 입력하시오 : ";
        std::cin>>n;
        std::cout<<std::endl;
        switch(n){
            case 1:
                //삽입내용
                if(database.size()>=5){
                    std::cout<<"database가 꽉 찼습니다.\n";
                    continue;
                }
                person_insert();
                break;
            case 2:
                //삭제
                if(database.size()<=0){
                    std::cout<<"database가 비어있습니다.\n";
                    continue;
                }
                person_delete();
                break;
            case 3:
               //수정
               if(database.size()<=0){
                    std::cout<<"database가 비어있습니다.\n";
                    continue;
                }
                person_update();
               break;
            case 4:
                //종료
                std::cout<<"프로그램을 종료합니다.\n";
                return -1;
                break;
            case 5:
               //검색
               if(database.size()<=0){
                    std::cout<<"database가 비어있습니다.\n";
                    continue;
                }
               search();
                break;
            default:
                //다시 선택하게 하기
                continue;
        }
    }
    return 0;
}

void person_insert(){
    struct person pi;           //삽입할 객체 생성
    std::cout<<"이름, 주소, 나이, 학번을 입력하시오\n";
    std::cin>>pi.name>>pi.address>>pi.age>>pi.haknum;

    database.insert(std::pair<unsigned int, person>(pi.haknum, pi));        //map에 삽입

    FILE *fp;                                                               //adr.dat파일에 삽입
    fp = fopen("adr.dat", "a");
    fwrite(&pi, sizeof(struct person), 1, fp);
    fclose(fp);
    print();                                                                //현재 데이터 베이스 출력
}

void person_delete(){
    unsigned int person_count = database.size();
    std::map<unsigned int, struct person>::iterator iter;
    
    unsigned int deletNum;
    std::cout<<"삭제할 학생의 학번을 입력하시오.\n학번 : ";
    std::cin>>deletNum;
    database.erase(deletNum);                                               //database 내에서의 삭제
    
    FILE *fp;
    struct person po[person_count];                                         //현재 있는 database 크기 만큼 객체 생성
    
    int i=0;
    for(iter = database.begin(); iter!=database.end(); iter ++){            //삭제된상태의 db를 객체에 삽입하여 파일에 쓰기
       po[i]=iter->second;
        i++;
    }
    fp = fopen("adr.dat", "w");
    fwrite(po, sizeof(struct person), person_count, fp);
    fclose(fp);
    print();                                                                 //현재 데이터 베이스 출력
    
}


void person_update(){
    unsigned int person_count = database.size();
    std::map<unsigned int, struct person>::iterator iter;

    unsigned int updateNum;
    std::cout<<"수정할 학생의 학번을 입력하시오.\n학번 : ";
    std::cin>>updateNum;
    struct person update;
    std::cout<<"수정할 내용의 이름, 주소, 나이, 학번을 입력하시오\n";
    std::cin>>update.name>>update.address>>update.age>>update.haknum;
    database.erase(updateNum);                                                              //수정할 db 삭제하고
    database.insert(std::pair<unsigned int, struct person>(updateNum, update));             //수정한 내용 새로 삽입
                                                                                            // 삭제 -> 삽입한 경우 기존 메모리크기대로 저장되는 문제발생
    FILE *fp;
    struct person po[person_count];
    
    int i=0;
    for(iter = database.begin(); iter!=database.end(); iter ++){                             //수정된 상태의 db를 객체에 삽입하여 파일에 쓰기
        po[i]=iter->second;
        i++;
    }
    fp = fopen("adr.dat", "w");
    fwrite(po, sizeof(struct person), person_count, fp);
    fclose(fp);

    print();
}

void search(){
    unsigned int searchNum;
    std::cout<<"검색할 학생의 학번을 입력하시오.\n학번 : ";
    std::cin>>searchNum;
    
    FILE *fp;
    unsigned int person_count = database.size();
    struct person po[person_count];

    if((fp = fopen("adr.dat", "r"))==NULL){
        printf("Error:could not open addr.dat.\n");
        exit (1);
    }
    fread(po, sizeof(struct person), person_count, fp);

    std::cout<<"\n***************************************************\n";
    std::cout<<"학번\t이름\t주소\t나이\n";
    std::cout<<"***************************************************\n";
    for(int i=0; i<person_count; i++)     //map을 사용하여 찾아내면 더 간단하고 빠르지만 파일 내의 값에서 search 하기 위해
        if(po[i].haknum == searchNum)
            std::cout<<po[i].haknum<<" / "<< po[i].name<<" / "<<po[i].address<<" / "<<po[i].age<<std::endl;
    
    fclose(fp);
}

void print(){   
    unsigned int person_count = database.size();
    
    std::map<unsigned int, struct person>::iterator iter;

    FILE *fp;
    struct person po[person_count];

    if((fp = fopen("adr.dat", "r"))==NULL){
       printf("Error:could not open addr.dat.\n");
       exit (1);
    }
    fread(po, sizeof(struct person), person_count, fp);
    
    std::cout<<"\n현재 데이터 베이스\n";
    std::cout<<"***************************************************\n";
    std::cout<<"학번\t이름\t주소\t나이\n";
    std::cout<<"***************************************************\n";
    for(int i=0; i<person_count; i++)
       std::cout<<po[i].haknum<<" / "<<po[i].name<<" / "<< po[i].address<<" / "<<po[i].age<<std::endl; 
    
}