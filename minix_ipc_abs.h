#include<lib.h>
#include<unistd.h>

int _topiclookup_(char *names){
	message m;
	m.m1_p1 = names;
	return (_syscall(PM_PROC_NR,PM_TLOOKUP,&m));
}

int _topiccreate_(int id,char *name){
	message m;
	m.m1_p1 = name;
	m.m1_i1 = id;
	return (_syscall(PM_PROC_NR,PM_TCREATETOPIC,&m));
}

int _topicsubscriber(int id,char *tname){
	message m;
	m.m1_p1 = name;
	m.m1_i1 = id;
	return (_syscall(PM_PROC_NR,PM_TSUBSCRIBER,&m));
}

int _topicpublisher(int id,char *tname){
	message m;
	m.m1_p1 = name;
	m.m1_i1 = id;
	return (_syscall(PM_PROC_NR,PM_TPUBLISHER,&m));
}

int _topicpublish_(char *tname, int id, char *msg){
	message m;
	m.m1_i1 = id;
	m.m1_p1 = tname;
	m.m1_p2 = msg;
	return (_syscall(PM_PROC_NR,PM_TPUBLISH,&m));
}

int _topicgetmessage_(char *tname,int id,char *message){
	message m;
	m.m1_i1 = id;
	m.m1_p1 = tname;
	m.m1_p2 = message;
	return (_syscall(PM_PROC_NR,PM_TGETMESSAGE,&m));
}

int _topicresetpage_(){
	return (_syscall(PM_PROC_NR,PM_TRESETPAGE,&m));
}
