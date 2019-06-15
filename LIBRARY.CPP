 #include<fstream.h>
 #include<conio.h>
 #include<iomanip.h>
 #include<string.h>
 #include<stdio.h>
 #include<dos.h>
 #include<ctype.h>
 #include<process.h>

 fstream f; fstream M; int N,temp=0,i,Mem; char choice,ch[50]; char found='t'; //ษปบศอผ

 void mainmenu(); void mship(); void searchby(); void search();
 void openlib(); void addbook();
 void lower(char bo[]){ int j=strlen(bo); for(i=0; i<j; i++)
					   bo[i]=tolower(bo[i]); }
 void xy(int x,int y) { gotoxy(x,y); }
 void tc(int tc) { textcolor(tc); }
 void tb(int tb) { textbackground(tb); }
 void box(int x1,int x2,int y1,int y2,int c=0)
 { tc(3);
   for(i=x1; i<=x2; i++)
    { xy(i,y1); cprintf("อ"); xy(i,y2); cprintf("อ");}
   for(i=y1; i<=y2; i++)
    { if(c==0){xy(x1,i); cprintf("บ"); xy(x2,i); cprintf("บ");}
      xy(x1-1,i); cprintf("บ"); xy(x2+1,i); cprintf("บ");}
   xy(x1-1,y1); cprintf("ษ"); xy(x2+1,y1); cprintf("ป");
   xy(x1-1,y2); cprintf("ศ"); xy(x2+1,y2); cprintf("ผ");
 }
 struct book
 { char bn[50],bw[50],bp[50],sub[20];
   int strd,cop;
   float price;
 }b;

 struct member
  { char mn[50],isbk[50];
    int dt,mon,ye;
    float fine;
  }m;

 void nor()
  { f.open("book.dat",ios::binary|ios::in); f.seekg(0,ios::end);
    M.open("member.dat",ios::binary|ios::in); M.seekg(0,ios::end);
    Mem=(M.tellg()/sizeof(m)); N=(f.tellg()/sizeof(b));
    M.close(); f.close(); box(54,78,1,4,1);
    xy(55,2); cprintf("Total distinct books="); cout<<N;
    xy(55,3); cprintf("Total members="); cout<<Mem<<endl;
  }

 void disbk(int rn) 			 //display book
 { f.seekg(sizeof(b)*(rn-1),ios::beg);
   f.read((char*)&b,sizeof(b));
  {  cout<<"\t\t\t\tBook name: ";      cout<<b.bn<<endl;
     cout<<"\t\t\t\tBook writer: ";    cout<<b.bw<<endl;
     cout<<"\t\t\t\tBook publisher: "; cout<<b.bp<<endl;
     cout<<"\t\t\t\tSubject: ";        cout<<b.sub<<endl;
     cout<<"\t\t\t\tStandard: ";       cout<<b.strd<<endl;
     cout<<"\t\t\t\tPrice: ";          cout<<b.price<<endl;
     cout<<"\t\t\t\tNo. of copies: ";  cout<<b.cop<<"\n\n\n";
  }
 }

 void mainmenu()
 { tc(7); clrscr(); nor();
  { box(30,50,1,8);
    tc(2); xy(31,2); cprintf(" <:> MAIN MENU <:>");
    tc(3); xy(31,3); cprintf("อออออออออออออออออออ");
    xy(34,4); cout<<"1.OPEN LIBRARY";
    xy(34,5); cout<<"2.MEMBERSHIP";
    xy(34,6); cout<<"3.EXIT";
    xy(32,7); cout<<"Your choice:"; }
  cin.get(choice);
  switch(choice)
   { case '1': openlib(); break;
     case '2': mship(); break;
     case '3': clrscr(); xy(34,13); cout<<"Thank you!!!";
	       getch(); exit(0);
     default : mainmenu();
   }
 }

 int fine(int day,int mon,int year)
 { struct date r;
   getdate(&r); int fine; int d=0,m=0,y=0,l=7;
   if(day==31) day=30;
   if(day+l>30) { mon=mon+((day+l)/30); day=(day+l)%30;
		  if(mon>12) { year++; mon=mon%12; }}
   else day=day+l;
   if((int)r.da_year==year&&(int)r.da_mon==mon)
    if(day>=(int)r.da_day)
     return 0;
   if((int)r.da_year>=year)
    { m=(int)r.da_mon-mon;
      d=(int)r.da_day-day;
      y=(int)r.da_year-year; }
   fine=y*360+m*30+d; return fine;
 }

 void mship()
 { tc(7); clrscr(); temp=0; box(20,60,6,12); found='t'; nor();
   xy(24,7); cout<<"1.Add memeber / Issue a book.";
   xy(24,8); cout<<"2.Remove member / return a book.";
   xy(24,9); cout<<"3.View all members.";
   xy(24,10); cout<<"4.Back";
   xy(22,11); cout<<"Your choice:";
   cin.get(choice);
   switch(choice)
    { case '1': tc(7); clrscr(); struct date d;
		cout<<"\n\tEnter name of book you want to issue:";
		gets(ch); lower(ch);
		f.open("book.dat",ios::binary|ios::in|ios::out);
		M.open("member.dat",ios::binary|ios::app);
		f.read((char*)&b,sizeof(b));
		while(f)
		 { temp++;
		   if(strcmp(ch,b.bn)==0)
		    { cout<<"\n\t\t\t\tBook details\n\n"; disbk(temp);
		      if(b.cop!=0)
		       { cout<<"Enter member name:"; gets(m.mn); lower(m.mn);
			 strcpy(m.isbk,b.bn); m.fine=0; --b.cop; getdate(&d);
			 m.dt=d.da_day; m.mon=d.da_mon; m.ye=d.da_year;
			 cout<<"Date to issue:"<<m.dt<<"-"<<m.mon<<"-"<<m.ye;
			 f.seekp((temp-1)*sizeof(b));
			 f.write((char*)&b,sizeof(b));
			 M.write((char*)&m,sizeof(m)); found='i';
		       } else cout<<"\t\t\t\tOut of stock!!"; found='f';
		      break;}
		   f.read((char*)&b,sizeof(b));
		 } cout<<endl;
		   if(found=='t') cout<<"\n\tBook not found";
		   if(found=='i') cout<<"\n\tThe book has been issued...";
		 M.close(); f.close(); getch(); mship(); break;
      case '2': tc(7); clrscr(); temp=0; fstream t; N=0;
		cout<<"\n\tEnter member name:"; gets(ch); lower(ch);
		t.open("temp.dat",ios::binary|ios::out);
		M.open("member.dat",ios::binary|ios::in|ios::out);
		f.open("book.dat",ios::binary|ios::in|ios::out);
		M.read((char*)&m,sizeof(m));
		while(M)
		 { temp++;
		   if(strcmp(ch,m.mn)==0)
		    { cout<<"\n\t\t\t\tMember details\n\n";
		     { cout<<"\t\t\t\tMember name:"<<m.mn;
		       cout<<"\n\t\t\t\tBook issued:"<<m.isbk;
		       cout<<"\n\t\t\t\tDate to issue:";
		       cout<<m.dt<<"-"<<m.mon<<"-"<<m.ye;
		       m.fine=fine(m.dt,m.mon,m.ye);
		       cout<<"\n\t\t\t\tFine:"<<m.fine; }
		      f.read((char*)&b,sizeof(b));
		      while(f) //to edit no. of copies
		       { N++;
			 if(strcmp(b.bn,m.isbk)==0)
			  { ++b.cop; f.seekp((N-1)*sizeof(b));
			    f.write((char*)&b,sizeof(b)); break;}
			 f.read((char*)&b,sizeof(b));
		       }
		      found='f';
		    }
		   else t.write((char*)&m,sizeof(m)); //to delete member
		   M.read((char*)&m,sizeof(m));
		 } M.close(); f.close(); t.close();
		remove("member.dat"); rename("temp.dat","member.dat");
		if(found=='f') { cout<<"\n\tMEMBER has been deleted ";
				 cout<<"& BOOK has been returned...";
			       }
		else cout<<"\n\tMEMBER not found!!"; getch(); mship(); break;
      case '3': tc(7); clrscr(); M.open("member.dat",ios::binary|ios::in);
		M.read((char*)&m,sizeof(m));
		 while(M)
		  { temp++; M.seekg((temp-1)*sizeof(m));
		    M.read((char*)&m,sizeof(m));
		    cout<<"\t\t\t\t<<<<<<"<<temp<<">>>>>>\n\n";
		    cout<<"\t\t\t\tMember name:"<<m.mn;
		    cout<<"\n\t\t\t\tBook issued:"<<m.isbk;
		    cout<<"\n\t\t\t\tDate to issue:";
		    cout<<m.dt<<"-"<<m.mon<<"-"<<m.ye;
		    m.fine=fine(m.dt,m.mon,m.ye);
		    cout<<"\n\t\t\t\tFine:"<<m.fine<<"\n\n\n";
		   if(temp%3==0)
		   { xy(2,24); cout<<"<p> to see previous members.";
		     xy(52,24); cout<<"<l> to see more members.";
		     xy(79,24); cin>>choice;
		     switch(choice) { case'p':temp-=6; clrscr(); break;
				      case'l':clrscr(); break;
				      default:temp-=3; clrscr(); break; }
		   } if(temp<0 || Mem==temp) break;
		} M.close(); getch(); mship(); break;
      case '4': mainmenu();
      default : mship();
    }
 }

 void openlib()
 { tc(7); clrscr(); char bookn[50]; nor(); found='t'; temp=0;
     box(26,50,1,11);
     xy(30,2); cout<<"1.Search BOOKS";
     xy(30,3); cout<<"2.View all books";
     xy(30,4); cout<<"3.Add book/books";
     xy(30,5); cout<<"4.Delete book";
     xy(30,6); cout<<"5.Edit book details";
     xy(30,7); cout<<"6.Delete all";
     xy(30,8); cout<<"7.BACK";
     xy(28,10); cout<<"Your choice:";
   cin.get(choice);
   switch(choice)
   { case '1': searchby(); break;
     case '2': tc(7); clrscr(); f.open("book.dat",ios::binary|ios::in);
	       while(temp<N && temp>=0)
		{ temp++; cout<<"\t\t\t\t<<<<<<"<<temp<<">>>>>>\n\n";
		  disbk(temp);
		  if((temp%2==0)||(temp==N && N%2!=0))
		   { xy(2,24); cout<<"<p> to see previous books.";
		     xy(52,24); cout<<"<l> to see more books.";
		     xy(79,24); cin>>choice; if(temp%2!=0) temp++;
		     switch(choice) { case'p':temp-=4; clrscr(); break;
				      case'l':clrscr(); break;
				      default:temp-=2; clrscr(); break; }
		   }
		} f.close(); getch(); openlib(); break;
     case '3': addbook(); break;
     case '4': tc(7); clrscr();
	       cout<<"\n\n\n\tEnter name of book to delete its all copies:";
	       gets(bookn); lower(bookn); fstream t;
	       cout<<"\tEnter price of book too:"; cin>>temp;
	       f.open("book.dat",ios::binary|ios::in);
	       t.open("temp.dat",ios::binary|ios::out);
	       f.read((char*)&b,sizeof(b));
	       while(f)
		{ if(strcmp(bookn,b.bn)!=0||temp!=b.price)
		  t.write((char*)&b,sizeof(b));
		  else found='f';
		  f.read((char*)&b,sizeof(b));
		} f.close(); t.close();
	       remove("book.dat"); rename("temp.dat","book.dat");
	       if(found=='f') cout<<"\t\t\t\tbook has been deleted!!";
	       else cout<<"\t\t\t\tNO book found!!";
	       getch(); openlib(); break;
     case '5': tc(7); clrscr(); cout<<"\n\tEnter book name:"; gets(bookn);
	       lower(bookn);
	       f.open("book.dat",ios::binary|ios::in|ios::out);
	       f.read((char*)&b,sizeof(b)); found='t';
	       while(f)
		{ temp++;
		  if(strcmp(bookn,b.bn)==0)
		   { cout<<"\n\t\t\t\tMember details\n\n";
		     disbk(temp);  found='f';
		     cout<<"\n\t<1> to edit name."<<endl;
		     cout<<"\t<2> to edit writer."<<endl;
		     cout<<"\t<3> to edit publisher."<<endl;
		     cout<<"\t<4> to edit subject"<<endl;
		     cout<<"\t<5> to edit standard."<<endl;
		     cout<<"\t<6> to edit price."<<endl;
		     cout<<"\t<7> to edit no. of copies."<<endl;
		     cout<<"\tyour choice:"; cin>>choice; cout<<"\t\t\t\t";
		     switch(choice)
		      { case '1': cout<<"Book name:"; gets(b.bn); break;
			case '2': cout<<"Book writer:"; gets(b.bw); break;
			case '3': cout<<"Book publisher:"; gets(b.bp); break;
			case '4': cout<<"Subject:"; gets(b.sub); break;
			case '5': cout<<"Standard:"; cin>>b.strd; break;
			case '6': cout<<"Price:"; cin>>b.price; break;
			case '7': cout<<"No. of copies:"; cin>>b.cop; break;
			default: f.close(); openlib();
		      }
		     f.seekp((temp-1)*sizeof(b));
		     f.write((char*)&b,sizeof(b));
		     cout<<"\n\t\t\t\tThe book has been modified..!!";
		   }
		  f.read((char*)&b,sizeof(b));
		} if(found=='t') cout<<"\t\t\t\tNo book found..!!";
	       f.close(); getch(); openlib(); break;
     case '6': tc(7); clrscr();
	       cout<<"\n\t\tEnter password to proceed:";
	       char pw[10]; cin>>pw;
	       if(strcmp(pw,"13579")==0)
		{ remove("book.dat");
		  cout<<"\t\t\t\tAll books are deleted.."; }
	       else exit(0);
	       getch(); openlib(); break;
     case '7': mainmenu(); break;
     default: openlib();
   }
 }

 void addbook()
 { tc(7); clrscr(); nor(); char chr;
   f.open("book.dat",ios::binary|ios::app);
   do{ cout<<"\tBook name:      "; gets(b.bn); lower(b.bn);
       cout<<"\tBook writer:    "; gets(b.bw); lower(b.bw);
       cout<<"\tBook publisher: "; gets(b.bp); lower(b.bp);
       cout<<"\tSubject:        "; gets(b.sub);lower(b.sub);
       cout<<"\tStandard (1-12):"; cin>>b.strd;
       cout<<"\tPrice:          "; cin>>b.price;
       cout<<"\tNo. of copies:  "; cin>>b.cop;
       f.write((char*)&b,sizeof(b));
       cout<<"\n\tEnter more records:(y/n)";
       cin>>chr; cout<<endl;
     }while(chr=='Y'||chr=='y');
   f.close(); openlib();
 }

 void search(char h[],char ch[])
  { found='t'; temp=0; lower(ch); char c;
    while(f) { ++temp;
	       if(strcmp(ch,h)==0)
		{ disbk(temp); found='f'; cout<<"\tsee more(y/n)";
		  cin>>c; if(c!='y'&&c!='Y') break;}
	      f.read((char*)&b,sizeof(b));
	     }
    if(found=='t') cout<<"\n\t\t\t\tNo book found";
  }

 void searchby()
 { tc(7); clrscr(); nor(); temp=0; found='t';
    box(29,49,1,11);
    tc(7); xy(31,2); cprintf("<:> SEARCH BY <:>");
    tc(3); xy(30,3); cprintf("อออออออออออออออออออ");
    xy(33,4); cout<<"1. Name ";
    xy(33,5); cout<<"2. Writer ";
    xy(33,6); cout<<"3. Subject ";
    xy(33,7); cout<<"4. Class ";
    xy(33,8); cout<<"5. BACK ";
    xy(31,10); cout<<"Your Choice: ";
    cin.get(choice); tc(7); clrscr();
   f.open("book.dat",ios::binary|ios::in);
   f.read((char*)&b,sizeof(b));
   switch(choice)
    { case '1': cout<<"\n\tEnter name to search: ";
		gets(ch); search(b.bn,ch); break;
      case '2': cout<<"\n\tEnter book writer's name: ";
		gets(ch); search(b.bw,ch); break;
      case '3': cout<<"\n\tEnter subject to search by: ";
		gets(ch); search(b.sub,ch); break;
      case '4': cout<<"\n\tEnter class to search by: "; cin>>N; char c;
		if(isdigit(N)==0)
		 while(f){ ++temp;
			   if(N==b.strd)
			    { disbk(temp); found='f';
			      cout<<"\tsee more(y/n)";cin>>c;
			      if(c!='y'&&c!='Y') break;}
			   f.read((char*)&b,sizeof(b)); }
		else exit(0);
		if(found=='t') cout<<"\n\t\t\t\tNo book found!!";
		break;
      case '5': openlib();
      default: searchby();
    } f.close(); getch(); searchby();
 }

 void main()
 { tb(0); clrscr(); mainmenu(); getch();}
