/*
 * testDate.cxx
 *
 *  Created on: Mar 2, 2016
 *      Author: sid
 */
#include "date.h"
#include <iostream>
#include <string.h>
#include <stdexcept>
#include <ctime>
#include <fstream>
using namespace std;
class Date;
class DateFormat;
int main(){
	ofstream fout("report.txt");
	Date d;
	fout<<"#########################################";
	fout<<"1. >>>Checking Constructors of Date\n\n";


	fout<<"(i) --Date::Date(Day,Month,Year)\n";
	fout<<"Random valid case:\n";
	fout<<Date(D31,Dec,2049);
	fout<<Date(D29,Feb,2016);
	fout<<Date(D31,Jan,2013);
	fout<<Date(D01,Jan,2001);
	fout<<"\nInvalid cases:\n";
	try{
		fout<<"29-Feb-2015\n";
		Date(D29,Feb,2015);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	try{
		fout<<"31-Dec-1949\n";
		Date(D31,Dec,1949);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}

	try{
		fout<<"01-Jan-2050\n";
		Date(D01,Jan,2050);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	try{
		fout<<"31-Apr-2015\n";
		Date(D31,Apr,2015);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	try{
		fout<<"31-Sep-2015\n";
		Date(D31,Sep,2015);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	try{
		fout<<"31-13-2015\n";
		Date(D31,(Month)13,2015);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	try{
		fout<<"34-Apr-2015\n";
		Date(Day(34),Apr,2015);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}

	fout<<"----------------------------------------\n";
	fout<<"(ii) Date::Date()  default constructor\n";
	try{
		fout<<Date();
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}

	fout<<"----------------------------------------\n";
		fout<<"(iii) Date::Date(Date&)  copy constructor\n";
	try{
		Date d1;
		fout<<"d1= "<<d1;
		fout<<"Date d2= new Date(*d1)\n";
		Date *d2=new Date(d1);
		fout<<"d2= "<<*d2;
		Date d3=d1;
		fout<<"Date d3=d1\n";
		fout<<"d3= "<<d3;
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	catch(domain_error &e){fout<<e.what()<<"\n";}
	catch(out_of_range &e){fout<<e.what()<<"\n";}
	fout<<"####################################\n\n";


	fout<<"2. >>> checking DateFormat and Date(const char*) constructor of Date";

	fout<<"\n(i) Checking constructor-> DateFormat::DateFormat(const char*)-\n";
	fout<<"invalid formats:\n";
	try{
		fout<<"-random word- 'erascfw'\n";
		DateFormat("erascfw");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"'dd-mm-yyyy-' (more than 2 hyphens)\n";
		DateFormat("dd-mm-yyyy- ");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"'d-mm' less than two hyphen\n";
		DateFormat("d-mm");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"NULL\n";
		DateFormat(NULL);
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"Empty string \n";
		DateFormat("");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"ddd-mm-yy \n";
		DateFormat("ddd-mm-yy");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"dd-mm-yyy\n";
		DateFormat("dd-mm-yyy");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"d-mmm-y\n";
		DateFormat("d-mmm-y");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}
	try{
		fout<<"x-zz-wwww\n";
		DateFormat("x-zz-wwww");
	}catch(invalid_argument &e){ fout<<e.what()<<"\n";}

	fout<<"------Trying some valid formats--\n";
	try{
		fout<<"dd-mm-yyyy\n";
		DateFormat("dd-mm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"d-mm-yyyy\n";
		DateFormat("d-mm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"-mm-yyyy (DayFormat is NULL)\n";
		DateFormat("-mm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd--yyyy (MonthFormat is NULL\n";
		DateFormat("dd--yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-m-yyyy\n";
		DateFormat("dd-m-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-mm-yyyy\n";
		DateFormat("dd-mm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-mmm-yyyy\n";
		DateFormat("dd-mmm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-mm-  (YearFormat is NULL)\n";
		DateFormat("dd-mm-");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-mm-yy\n";
		DateFormat("dd-mm-yy");
	}catch(...){ fout<<"FAIL!"<<"\n";}
	try{
		fout<<"dd-mm-yyyy\n";
		DateFormat("dd-mm-yyyy");
	}catch(...){ fout<<"FAIL!"<<"\n";}

	fout<<"------------------------------------\n";
	fout<<"(ii)Checking Date::Date(const char*) constructor\n";

	//fout<<"trying some invalid cases\n";
	fout<<"Current format is dd-mm-yy\n";
	DateFormat *f= new DateFormat("dd-mm-yy");
	d.setFormat(*f);
	try{
		fout<<"a. 22-1-2016\n";
		fout<<Date("22-01-2016");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"b. 22-1-16\n";
		fout<<Date("22-1-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"c. 9-01-16\n";
		fout<<Date("9-01-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"d. 29-02-15\n";
		fout<<Date("29-02-15");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"e. 33-01-15\n";
		fout<<Date("33-01-15");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"f. 29-02-16\n";
		fout<<Date("29-02-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	//TODO other formats;

	fout<<"change format to d-m-yy\n";
	DateFormat* g=new DateFormat("d-m-yy");
	d.setFormat(*g);
	try{
		fout<<"a. 22-1-2016\n";
		fout<<Date("22-01-2016");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"b. 22-1-16\n";
		fout<<Date("22-1-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"c. 9-01-\n";
		fout<<Date("9-01-");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"d. 09-02-15\n";
		fout<<Date("09-02-15");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"e. 9-2-15\n";
		fout<<Date("9-2-15")<<endl;
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"f. 29-2-16\n";
		fout<<Date("29-2-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}

	fout<<"change format to d-m-yyyy\n";
	DateFormat* h=new DateFormat("d-m-yyyy");
	d.setFormat(*h);
	try{
		fout<<"a. 22-1-2016\n";
		fout<<Date("22-1-2016");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"b. 22-1-16\n";
		fout<<Date("22-1-16");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"c. 9-01-\n";
		fout<<Date("9-01-");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"d. 09-2-2015\n";
		fout<<Date("09-2-2015");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"e. 9-2-15\n";
		fout<<Date("9-2-15")<<endl;
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	try{
		fout<<"f. 29-2-2015\n";
		fout<<Date("29-2-2015");
	}catch(invalid_argument &e){fout<< e.what()<<"\n";}
	catch(domain_error &e){fout<< e.what()<<"\n";}
	catch(out_of_range &e){fout<< e.what()<<"\n";}
	fout<<"--------------------------------------\n";
	fout<<"(iii)Testing DateFormat::DateFormat(const char*df ,const char* mf,const char* yf) \n";
	fout<<"some invalid cases:\n";
	try{
		fout<<"NULL\n";
		DateFormat(0);
	}catch(invalid_argument &e){fout<<e.what()<<endl;}
	try{
		fout<<"dd-mm-yyy\n";
		DateFormat("dd","mm","yyy");
	}catch(invalid_argument &e){fout<<e.what()<<endl;}
	try{
		fout<<"ddd-mmm-yy\n";
		DateFormat("ddd","mmm","yy");
	}catch(invalid_argument &e){fout<<e.what()<<endl;}
	try{
		fout<<"empyty-empty-empty\n";
		DateFormat("","","");
	}catch(invalid_argument &e){fout<<e.what()<<endl;}
	fout<<"\n valid cases\n";
	try{
		fout<<"dd-mm-yyyy\n";
		DateFormat("dd","mm","yyyy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"dd-mm-yy\n";
		DateFormat("dd","mm","yy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"d-mm-yyyy\n";
		DateFormat("d","mm","yyyy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"d-m-yy\n";
		DateFormat("d","m","yy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"dd-mmm-yyyy\n";
		DateFormat("dd","mmm","yyyy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"-mm-yy\n";
		DateFormat("0","mm","yy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"dd--yyyy\n";
		DateFormat("dd","0","yyyy");
	}catch(...){fout<<"error!";}
	try{
		fout<<"dd-m-\n";
		DateFormat("dd","m","0");
	}catch(...){fout<<"error!";}


	fout<<"########################################\n\n";
	fout<<"Checking unary operators\n";
	Date du;
	fout<<"current date- "<<du;
	fout<<"++du "<<++du<<endl;
	fout<<"du++ "<<du++<<endl;
	fout<<"du-- "<<du--<<endl;
	fout<<"--du "<<--du<<endl;
	du=Date("30-12-2049");
	fout<<"current date- "<<du;
	try{
		fout<<"++du ";
		fout<<++du<<endl;
	}catch(out_of_range& e){fout<<e.what()<<endl;}
	try{
		fout<<"du++ ";
		fout<<du++<<endl;
	}catch(out_of_range &e){fout<<e.what()<<endl;}
	du=Date("2-1-1950");
	fout<<"current date- "<<du;
	try{
		fout<<"--du ";
		fout<<--du<<endl;
	}catch(out_of_range& e){fout<<e.what()<<endl;}
	try{
		fout<<"du-- ";
		fout<<du--<<endl;
	}catch(out_of_range &e){fout<<e.what()<<endl;}
	du=Date("1-3-2016");
	fout<<"current date- "<<du;
	try{
		fout<<"--du ";
		fout<<--du<<endl;
	}catch(out_of_range& e){fout<<e.what()<<endl;}
	try{
		fout<<"du-- ";
		fout<<du--<<endl;
	}catch(out_of_range &e){fout<<e.what()<<endl;}
	fout<<"#####################################\n\n";
	fout<<"checking binary operators:\n checking '-' \n";
	try{
		Date dd=Date("3-3-2016");
		Date d1=Date("29-2-2016");
		fout<<"3-3-2016 "<<" - "<<"29-2-2016 "<<" = "<<dd-d1<<endl;
		fout<<"29-2-2016 "<<" - "<<"3-3-2016 "<<" = "<<dd-d1<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}
	try{
		Date dd=Date("3-3-2016");
		Date d1=Date("2-6-1988");
		fout<<"3-3-2016 "<<" - "<<"2-6-1988 "<<" = "<<dd-d1<<endl;
		fout<<"2-6-1988 "<<" - "<<"3-3-2016 "<<" = "<<dd-d1<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}
	fout<<"-----------------------\nchecking ' + ' \n";
	try{
		Date dd=Date("3-3-2016");
		fout<<"3-3-2016 "<<" + "<<" 5 "<<" = "<<dd + 5<<endl;
		fout<<"28-2-2016 "<<" + "<<" 6 "<<" = "<<Date("28-2-2016") + 6<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}
	try{
		Date dd=Date("31-12-2049");
		fout<<"31-12-2049 "<<" + "<<" 1 "<<" = ";
		fout<<dd + 1<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}
	try{
		Date dd=Date("31-12-2016");
		fout<<"31-12-2016 "<<" + "<<" 1 "<<" = ";
		fout<<dd + 1<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}
	try{
		Date dd=Date("28-2-2016");
		fout<<"28-2-2016 "<<" + "<<" 1 "<<" = ";
		fout<<dd + 1<<endl;
	}catch(exception &e){fout<<e.what()<<endl;}

	fout<<"######################################\n";
	fout<<"checking relational ops\n";
	Date da=Date(D01,Jan,2016);
	Date db=Date(D29,Feb,2016);
	Date dc=Date(D31,May,2015);
	Date dd=da;
	fout<<"comparing the following dates\n";
	fout<<"da "<<da;
	fout<<"db "<<db;
	fout<<"dc "<<dc;
	fout<<"dd "<<dd;
	fout<<"da==db "<<(da==db)<<endl;
	fout<<"da<db "<<(da<db)<<endl;
	fout<<"da<dc "<<(da<dc)<<endl;
	fout<<"dd<da "<<(dd<da)<<endl;
	fout<<"dd<=da "<<(dd<=da)<<endl;
	fout<<"da==dd "<<(da==dd)<<endl;
	fout<<"dd>da "<<(dd>da)<<endl;
	fout<<"dd>=da "<<(dd>=da)<<endl;
	fout<<"da!=dd "<<(da!=dd)<<endl;

	fout<<"############################\n";
	fout<<"checking cast operators\n";
	fout<<"1. WeekDay\n";
	Date dw;
	fout<<dw;
	fout<<"WeekDay "<<WeekDay(dw)<<endl;
	dw=Date(D01,Jan,2016);
	fout<<dw;
	fout<<"WeekDay "<<WeekDay(dw)<<endl;
	dw=Date(D31,Dec,2016);
	fout<<dw;
	fout<<"WeekDay "<<WeekDay(dw)<<endl;
	fout<<"\n2. WeekNumber\n";
	dw=Date(D01,Jan,2015);
	fout<<dw;
	fout<<"WeekNumber "<<WeekNumber(dw)<<endl;
	dw=Date(D01,Jan,2016);
	fout<<dw;
	fout<<"WeekNumber "<<WeekNumber(dw)<<endl;
	dw=Date(D31,Dec,2016);
	fout<<dw;
	fout<<"WeekNumber "<<WeekNumber(dw)<<endl;
	fout<<Date();
	fout<<"WeekNumber "<<WeekNumber(Date())<<endl;
	fout<<"\n3.Month\n";
	dw=Date(D29,Feb,2016);
	fout<<dw;
	fout<<"Month "<<Month(dw)<<endl;
	dw=Date(D24,Mar,2034);
	fout<<dw;
	fout<<"Month "<<Month(dw)<<endl;
	return 0;
}
