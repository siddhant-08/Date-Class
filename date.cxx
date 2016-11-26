/*
 * Date.cxx
 *
 *  Created on: Mar 2, 2016
 *      Author: sid
 */

#include "date.h"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <string.h>
#include <fstream>
#include<string>
#include<stdlib.h>
//ofstream fout("report.txt");
using namespace std;

DateFormat Date::format;

void DateFormat::freeAll(){
 	delete[] dateFormat;
 	delete[] monthFormat;
 	delete[] yearFormat;
 	dateFormat=monthFormat=yearFormat=NULL;
 };

DateFormat::DateFormat(const char* format){
    if(format==NULL)throw (invalid_argument("No string entered\n"));
	dateFormat=new char[5];
    monthFormat=new char[5];
    yearFormat=new char[5];
    int len=strlen(format);
    int h[2]={0},p=0; // positions of hyphens
    for(int i=0;i<len;i++){
        if(format[i]=='-'){
            h[p]=i;
            p++;
            if(p>2){
            	throw invalid_argument("invalid format of date");
            }
        }
    }
    // less than 2 '-'
    if(p!=2){
        //cout<<"p!=2";
    	throw invalid_argument("invalid format of date");
    }

    if(h[0]==1)// d is valid
    {
        if(format[0]!='d')
        	throw invalid_argument("invalid format of date");
    	dateFormat[0]=format[0];
        dateFormat[1]='\0';

    }else if(h[0]==2) //dd
    {
        if(format[0]!='d' || format[1]!='d')
        	throw invalid_argument("invalid format of date");
		strcpy(dateFormat,"dd");
    }else if(h[0]>2){
    	throw invalid_argument("invalid format for day");
    }else{//h[0]==0
    	//string of type "-mf-yf"
    	dateFormat=NULL;
    }

    if(h[1]-h[0] - 1 == 1)//  m
    {
       if(format[h[0] + 1]!='m') // character is not m
    	   throw invalid_argument("invalid format of month");
    	monthFormat[0]=format[h[0] + 1];
    	monthFormat[1]='\0';
        //cout<<monthFormat<<"\n\n";
    }else if(h[1]-h[0] - 1==2)//mm
    {
        if(format[h[0] +1]!='m' || format[h[0] + 2]!='m') // not "mm"
        	throw invalid_argument("invalid format of month");
		strcpy(monthFormat,"mm");
    }else if(h[1]-h[0]-1==3) //mmm
    {
    	if(format[h[0] +1]!='m' || format[h[0] + 2]!='m' || format[h[0] + 3]!='m') // not "mm"
				throw invalid_argument("invalid format of month");
		strcpy(monthFormat,"mmm");
    }else if(h[1]-h[0]-1>3){
    	freeAll();
    	throw invalid_argument("invalid format for month");
    }else{
    	// string of type "df--yf"
    	monthFormat=NULL;
    }
    //year
    if(len -h[1]-1 ==2){ //yy
    	if(format[h[1] +1]!='y' || format[h[1] + 2]!='y')
    		throw invalid_argument("invalid format for year");
        strcpy(yearFormat,"yy");
    }else if(len -h[1] -1 ==4){
    	if(format[h[1] +1]!='y' || format[h[1] + 2]!='y'
			|| format[h[1] + 3]!='y' || format[h[1] + 4]!='y')
    		throw invalid_argument("invalid format for year");
    	strcpy(yearFormat,"yyyy");
    }else if(len - h[1] - 1==0){
        //string of type "df-mf-"
    	yearFormat=NULL;
    }else{
    	freeAll();
    	throw invalid_argument("invalid format for year");
    }
  }

DateFormat::DateFormat(const char* dateFormat, const char* monthFormat,const char* yearFormat)throw(invalid_argument){
        if(strcmp("0",dateFormat) && strcmp("d",dateFormat) && strcmp("dd",dateFormat))
        		throw invalid_argument("invalid format of day");
        if(strcmp("0",monthFormat)&&strcmp("m",monthFormat)&&strcmp("mm",monthFormat) &&strcmp("mmm",monthFormat))
        	throw invalid_argument("invalid format of month");
        if(strcmp("0",yearFormat) && strcmp("yy",yearFormat)&& strcmp("yyyy",yearFormat))
        	throw invalid_argument("invalid format of date");
    else{
        this->dateFormat=new char[strlen(dateFormat) + 1];
        this->monthFormat=new char[strlen(monthFormat) + 1];
        this->yearFormat=new char[strlen(yearFormat) + 1];

        strcpy(this->dateFormat,dateFormat);
        strcpy(this->monthFormat,monthFormat);
        strcpy(this->yearFormat,monthFormat);
    }
  };

  //default
  DateFormat::DateFormat()
  {
    dateFormat=new char[3];
    monthFormat=new char[4];
    yearFormat=new char[3];

    strcpy(dateFormat,"dd");
    strcpy(monthFormat,"mmm");
    strcpy(yearFormat,"yy");
  }
  //getters for Dateformat
  const char* DateFormat::getDF(){
    return dateFormat;
  }
  const char* DateFormat::getMF(){
    return monthFormat;
  }
  const char* DateFormat::getYF(){
    return yearFormat;
  }
  //copy constructor
  DateFormat::DateFormat(const DateFormat& ndf){
    dateFormat=new char[5];
    monthFormat=new char[5];
    yearFormat=new char[5];
  }

  //setters for date format
  void DateFormat::setDF(const char* df){
    delete[] dateFormat;
    if(!(df==NULL || strcmp(df,"d") || strcmp(df,"dd")))
    	throw invalid_argument("Invalid argument for date format");
	dateFormat=NULL;
    if(df!=NULL){
    	dateFormat=new char[strlen(df) + 1];
    strcpy(dateFormat,df);
	}
  }
  void DateFormat::setMF(const char* mf){
    delete[] monthFormat;
    monthFormat=NULL;
    if(!(mf==NULL ||strcmp(mf,"m") ||strcmp(mf,"mm") || strcmp(mf,"mmm")))
    	throw invalid_argument("Invalid argument for month format");
    if(mf!=NULL)
    {
      monthFormat=new char[strlen(mf) + 1];
	  strcpy(monthFormat,mf);
    }
  }
  void DateFormat::setYF(const char* yf){
    delete[] yearFormat;
	  if(!(yf==NULL || strcmp(yf,"yy") || strcmp(yf,"yyyy")))
		 throw invalid_argument("Invalid argument for year format");
	  yearFormat=NULL;
	    if(yf!=NULL){
		  yearFormat=new char[strlen(yf) + 1];
	  strcpy(yearFormat,yf);
	}
  }

  DateFormat::~DateFormat(){
	  freeAll();
  }

   Date:: Date(Day d_, Month m_, Year y_) throw(invalid_argument,domain_error,out_of_range){
        if(d_>31 || m_>12 || d_<=0 || m_<=0){
            throw invalid_argument("invalid value of date");
        }
        if(!is_valid(d_,m_,y_)){
        	if((y_%4) && m_==Feb && d_==D29)
        		throw domain_error("29 feb on non-leap year!");
        	throw domain_error("Domain Error");
        }
        if(y_<50){
        	y_+=2000;
        }if(y_>=50 && y_<100){
        	y_+=1900;
        }
        if(y_>2049 || y_<1950){
            throw out_of_range("date out of range");
        }
        d=d_;
        m=m_;
        y=y_;
    }
    bool Date:: is_valid(Day d_, Month m_, Year y_){
        if(m_==2){
            if((y_%4)){
                if(d_>28){
                    return false;
                }
            }else{
                if(d_>29){
                    return false;
                }
            }
        }else if(m_==4 || m_==6 || m_==9 ||m_==11){
            if(d_>30){
                return false;
            }
        }
        return true;
    }

    /* constructor 2*/
    Date:: Date(const char* date)throw(invalid_argument, domain_error, out_of_range){
      if(date==NULL)throw(invalid_argument("No date entered"));

      char* df = const_cast<char*>(Date::format.getDF());
	  char* mf = const_cast<char*>(Date::format.getMF());
	  char* yf = const_cast<char*>(Date::format.getYF());
	  //cout<<strlen(df)<<strlen(mf)<<strlen(yf);
	  if(df==NULL || mf==NULL || yf==NULL)throw domain_error("can't know date as one of the dateFormats is NULL");

	  int a=0,b=0,c=0,len=strlen(date),h[2]={0},p=0,raise=1;

      for(int i=0;i<len;i++){
          if(date[i]=='-'){
              h[p]=i;
              p++;
              if(p>2)throw invalid_argument("invalid format of date");
          }
      }
      if(p!=2){ // not having 2 hyphens
          throw invalid_argument("invalid format");
      }
      // checking if current format matches the set static member format of the Date class

      if((len- h[1] - 1)!=strlen(yf))
    	  throw invalid_argument("Wrong year-format entered");

      // calculting the day,month and year
      for(int i=h[0]-1;i>=0;i--){
          a+=(raise*(date[i]-'0'));
          raise*=10;
      }
      if(h[0]==2)
    	  if(a<10 && strlen(df)==1)
    		  throw invalid_argument("invalid day-format");
      if(h[0]==1)
    	  if(strlen(df)!=1)
    		  throw invalid_argument("invalid day-format");
      raise=1;
      for(int i=h[1]-1;i>h[0];i--){
          b+=raise*(date[i]-'0');
          raise*=10;
      }
      if(h[1] - h[0] - 1 ==2)
		  if(b<10 && strlen(mf)==1)
			  throw invalid_argument("invalid month format");
      if(h[1] - h[0] - 1==1)
    	  if(strlen(mf)!=1)
    		  throw invalid_argument("invalid month format");
      raise=1;
      for(int i=len-1;i>h[1];i--){
          c+=raise*(date[i]-'0');
          raise*=10;
      }
      if(raise==100){ // year format is yy
          if(c<50){
              c+=2000;
          }else{
              c+=1900;
          }
      }
      Day d1=static_cast<Day>(a);
      Month m1=static_cast<Month>(b);
      Year y1=c;
      if(d1>31 || m1>12 || d1<=0 || m1<=0){
          //cout<<a<<"\n";
          //cout<<b<<endl;
          //cout<<c<<endl;
    	  throw invalid_argument("invalid value of date!!");
      }
      if(!is_valid(d1,m1,y1)){
    	  throw domain_error("domain error!!");
      }
      if(y1>2049 || y1<1950){
          throw out_of_range("date out of range !!");
      }
      d=d1;
      m=m1;
      y=y1;
    }

    /*constructor 3- default*/
    Date:: Date()throw(domain_error, out_of_range){
      time_t t = time(0);   // get time now
      struct tm * now = localtime( & t );
      y=(Year)(now->tm_year + 1900);
      m=(Month)(now->tm_mon + 1);
      d=(Day)(now->tm_mday);
      if(!is_valid(d,m,y))
    	  throw domain_error("invalid date");
      if(y>2049 || y<1950)
    	  throw out_of_range("date is out of range!");
    }

    //copy constructor
    Date::Date(const Date& copy){
          y=copy.getYear();
          m=copy.getMonth();
          d=copy.getDay();
	}

    Date::~Date(){}

    Day Date::getDay()const{ return d;}
    Month Date::getMonth() const{return m;}
    Year Date::getYear() const {return y;}

    bool Date::leapYear()const{
      if((y%4)){
        return false;
      }
      return true;
    }

    Date& Date:: operator=(const Date& copy){
      if(*this!=copy){
        y=copy.getYear();
        m=copy.getMonth();
        d=copy.getDay();
        return *this;
      }
      return *this;
    }

    /* operators*/
    Date& Date::operator++() throw(out_of_range){
      if(m==2){
        if(d<28){
          d=(Day)(d + 1);
          return *this;
        }else if(d==28){
          if(leapYear()){
            d=(Day)(d+1);
            return *this;
          }else{
            d=(Day)1;
            m=(Month)3;
          }
          return *this;
        }else if(d==29){
        	d=(Day)1;
        	m=(Month)3;
        	return *this;
        }
      }else if(m==4 || m==6 || m==9 || m==11){
        if(d<30){
            d=(Day)(d+1);
            return *this;
        }else{
            d=(Day)1;
            m=(Month)(m+1);
            return *this;
        }
      }else if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10){
        if(d<31){
          d=(Day)(d+1);
          return *this;
        }else{
          d=(Day)1;
          m=(Month)(m+1);
          return *this;
        }
      }else if(m==12){
        if(d<31){
          d=(Day)(d+1);
          return *this;
        }else{
          d=(Day)1;
          m=(Month)1;
          y=y+1;
          return *this;
        }
      }
      if(y>2049 || y<1950){
    	  throw out_of_range("Date becomes out of range");
      }
      return *this;
    }
    Date& Date::operator--()throw(out_of_range){
      if(m==3){
        if(d>1){
          d=(Day)(d - 1);
          return *this;
        }else if(d==1){
          if(leapYear()){
            d=(Day)(29);
            m=(Month)2;
            return *this;
          }else{
            d=(Day)28;
            m=(Month)2;
            return *this;
          }
        }
      }else if(m==2 || m==4 || m==6 || m==9 || m==11){
        if(d>1){
            d=(Day)(d-1);
            return *this;
        }else{
            d=(Day)31;
            m=(Month)(m-1);
            return *this;
        }
      }else if(m==12 || m==3 || m==5 || m==7 || m==8 || m==10){
        if(d>1){
          d=(Day)(d-1);
          return *this;
        }else{
          d=(Day)30;
          m=(Month)(m-1);
          return *this;
        }
      }else if(m==1){
        if(d>1){
          d=(Day)(d-1);
          return *this;
        }else{
          d=(Day)31;
          m=(Month)12;
          y=y-1;
          return *this;
        }
      }
      if(y>2049 || y<1950){
		  throw out_of_range("Date becomes out of range");
	  }

      return *this;
    }

  /*----------------------------------*/

  Date& Date::operator++(int)throw(out_of_range){
	for(int i=0;i<7;i++)
	{
		++(*this);
		if(y>=2050)
			throw out_of_range("out of range!!");
	}
	return *this;

  }

  Date& Date::operator--(int)throw(out_of_range){
    for(int i=0;i<7;i++){
        --(*this);
        if(y<1950)
        	throw out_of_range("out of range!!");
    }
    return *this;
  }
  /*---------------------------------------*/

  //cast operators
  Date::operator Month() const{
    return m;
  }

  Date::operator WeekNumber() const{
      //sourced from a stackoverflow ans;
    struct tm tm={0,0,12,d,m-1,y-1900,0};
	char buf[64];
	mktime(&tm);
	strftime(buf, sizeof buf, "%V", &tm);
	return static_cast<WeekNumber>(atoi(buf));
  }
  //
  Date::operator WeekDay() const{
    struct tm a={0,0,0};
    a.tm_year=(int)y -1900 ;
    a.tm_mon=(int)m-1;
    a.tm_mday=(int)d;
    mktime(&a);
    return (WeekDay)(a.tm_wday);
  }

  unsigned Date::operator -(const Date& otherDate){
    struct tm a = {0,0,0,(int)otherDate.getDay(),(int)otherDate.getMonth(),(int)otherDate.getYear()};
    struct tm b = {0,0,0,(int)d,(int)m,(int)y};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    unsigned diff;
    if((*this) > otherDate)
    	diff= (unsigned)(difftime(y, x) / (60 * 60 * 24));
    else
    	diff= (unsigned)(difftime(x, y) / (60 * 60 * 24));
    return diff;
  }
  //converts a dat to number of days from start of epoch
  long long int  Date::getnumdays(const Date& dd) {       /* convert date to day number */
  	  long long y, m;
  	  m = ((int)dd.getMonth() + 9)%12;                /* mar=0, feb=11 */
  	  y = dd.getYear() - m/10;                     /* if Jan/Feb, year-- */
  	  return y*365 + y/4 - y/100 + y/400 + (m*306 + 5)/10 + (dd.getDay() - 1);
    }
  // convert num of days to a date
  Date  Date::days_to_date(long long d) { /* convert day number to y,m,d format */
  	  Date  pd;
  	  long long y, ddd, mi;

  	  y = (10000*d + 14780)/3652425;
  	  ddd = d - (y*365 + y/4 - y/100 + y/400);
  	  if (ddd < 0) {
  	    y--;
  	    ddd = d - (y*365 + y/4 - y/100 + y/400);
  	    }
  	  mi = (52 + 100*ddd)/3060;
  	  pd.setYear(y + (mi + 2)/12);
  	  pd.setMonth((Month)((mi + 2)%12 + 1));
  	  pd.setDay((Day)(ddd - (mi*306 + 5)/10 + 1));
  	  return pd;
    }

  Date Date::operator+(int noOfDays)throw(domain_error, out_of_range){
    long long orig= getnumdays(*this);
    long long fin=orig + (long long)noOfDays;
    Date ret=days_to_date(fin);
    if(ret.getYear()>2049 || ret.getYear()<1950 )
    	throw out_of_range("out of range!!");
    return ret;
  }

  void Date::setDay(Day x){
	  d=x;
  }
  void Date::setMonth(Month x){
	m=x;
  }
  void Date::setYear(Year x){
	y=x;
  }

  //comparision operators
  bool Date::operator==(const Date& otherDate){
    if(d==otherDate.getDay() && m==otherDate.getMonth() && y==otherDate.getYear())
      return true;
    return false;
  }
  bool Date::operator!=(const Date& otherDate){
      if(d==otherDate.getDay() && m==otherDate.getMonth() && y==otherDate.getYear())
        return false;
      return true;
  }
  bool Date::operator<(const Date& otherDate){
    if(y < otherDate.getYear())
      return true;
    else if(y>otherDate.getYear())
      return false;
    else{
      if(m< otherDate.getMonth())
        return true;
      else if(m>otherDate.getMonth())
          return false;
      else{
        if(d< otherDate.getDay())
          return true;
        else if(d>=otherDate.getDay())
          return false;
      }
    }
    return false;
  }
  bool Date::operator<=(const Date& otherDate){
    if(y< otherDate.getYear())
      return true;
    else if(y>otherDate.getYear())
      return false;
    else{
      if(m< otherDate.getMonth())
        return true;
      else if(m>otherDate.getMonth())
          return false;
      else{
        if(d<= otherDate.getDay())
          return true;
        else if(d>otherDate.getDay())
          return false;
      }
    }
    return false;
  }
  bool Date::operator>(const Date& otherDate){
    if(y> otherDate.getYear())
      return true;
    else if(y<otherDate.getYear())
      return false;
    else{
      if(m> otherDate.getMonth())
        return true;
      else if(m<otherDate.getMonth())
          return false;
      else{
        if(d> otherDate.getDay())
          return true;
        else if(d>=otherDate.getDay())
          return false;
      }
    }
    return false;
  }
  bool Date::operator>=(const Date& otherDate){
    if(y> otherDate.getYear())
      return true;
    else if(y<otherDate.getYear())
      return false;
    else{
      if(m> otherDate.getMonth())
        return true;
      else if(m<otherDate.getMonth())
          return false;
      else{
        if(d>= otherDate.getDay())
          return true;
        else if(d<otherDate.getDay())
          return false;
      }
    }
    return false;
  }
  /*-----------------------------------------*/
  //Format function
   void Date::setFormat(DateFormat& ndf){
      format.freeAll();
	  format.setDF(ndf.getDF());
      format.setMF(ndf.getMF());
      format.setYF(ndf.getYF());

  }
  DateFormat& Date::getFormat(){
    return Date::format;
  }
  /*----------------------------------------------*/

  ostream& operator<<(ostream& fout , const Date& date){
    char* month=new char[15];
    char* df=new char[5];
    char* mf=new char[5];
    char* yf=new char[5];

    if((date.getFormat()).getDF() !=NULL)
    strcpy(df,(date.getFormat()).getDF());
    if((date.getFormat()).getMF() !=NULL)
	strcpy(mf,(date.getFormat()).getMF());
    if((date.getFormat()).getYF() !=NULL)

    strcpy(yf,(date.getFormat()).getYF());

    if(df!=NULL){
		if(!strcmp(df,"d")){
		  fout<<date.getDay()<<" - ";
		}
		else if(!strcmp(df,"dd")){
		  int dt=(int)date.getDay();
		  //leading 0 for single digits
		  if(dt<10){
			fout<<"0";
		  }
		  fout<<dt<<" - ";
		}
    }
    if(mf!=NULL)
    {
    	if(!strcmp(mf,"m")){
		  int mt=(int)date.getMonth();
		  fout<<mt<<" - ";
		}
		else if(!strcmp(mf,"mm")){
		  int mt=(int)date.getMonth();
		  if(mt<10){
			fout<<"0";
		  }
		  fout<<mt<<" - ";
		}
		else if(!strcmp(mf,"0")){
		  int mt=date.getMonth();
		  if(mt == 1){ strcpy(month,"January");}
		  if(mt== 2){ strcpy(month,"February");}
		  if(mt == 3){ strcpy(month,"March");}
		  if(mt == 4){ strcpy(month,"April");}
		  if(mt == 5){ strcpy(month,"May");}
		  if(mt == 6){ strcpy(month,"June");}
		  if(mt == 7){ strcpy(month,"July");}
		  if(mt == 8){ strcpy(month,"August");}
		  if(mt == 9){ strcpy(month,"September");}
		  if(mt == 10){ strcpy(month,"October");}
		  if(mt == 11){ strcpy(month,"November");}
		  if(mt == 12){ strcpy(month,"December");}
		  fout<<month<<" - ";
		}
		else if(!strcmp(mf,"mmm")){
		  int mt=date.getMonth();
		  if(mt == 1){ strcpy(month,"Jan");}
		  if(mt == 2){ strcpy(month,"Feb");}
		  if(mt == 3){ strcpy(month,"Mar");}
		  if(mt == 4){ strcpy(month,"Apr");}
		  if(mt == 5){ strcpy(month,"May");}
		  if(mt == 6){ strcpy(month,"Jun");}
		  if(mt == 7){ strcpy(month,"Jul");}
		  if(mt == 8){ strcpy(month,"Aug");}
		  if(mt == 9){ strcpy(month,"Sep");}
		  if(mt == 10){ strcpy(month,"Oct");}
		  if(mt == 11){ strcpy(month,"Nov");}
		  if(mt == 12){ strcpy(month,"Dec");}
		  fout<<month<<" - ";
		}
  }
  if(yf!=NULL)
  {
	  if(!strcmp(yf,"yy")){
		  int yr=(int)date.getYear();
		  if(yr<2010)
			  fout<<"0";
		  fout<<(yr%100)<<"\n";
		}else if(!strcmp(yf,"yyyy")){
		  int yr=(int)date.getYear();
		  fout<<yr<<"\n";
		}
  }
	return fout;
 }
  istream& operator>>(istream& fin,Date& date){
	  string s;
	  fin>>s;
	  //constructor with const char* called
	  date= Date(s.c_str()); // c-style string
	  return fin;

  }

