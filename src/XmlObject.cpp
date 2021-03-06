/*
 * \file XmlObject.cpp
 * \Zawiera definicje funkcji klas zwartych w pliku XmlObject.h
 *  Created on: 30 maj 2015
 *      Author: karol
 */
#include "XmlObject.h"

XmlObject::XmlObject(string xelem):element(xelem){}

void XmlObject::set_elem(string xelem)
{
	if(xelem=="\0")
		element.reserve(30);
	else
		element=xelem;
}

XmlObject::~XmlObject(){}

XmlObject_string::XmlObject_string(string xelem,string xname):XmlObject(xelem),name(xname)
{
	if(name=="\0")
		name.reserve(30);
}

XmlObject_string::~XmlObject_string(){}

string XmlObject_string::to_xml()
{
	stringstream tmp;
	string strm;
	if(element=="\0")
	{
		cerr<<"Pusty element w XmlObject_string."<<endl;
		return 0;
	}
	tmp<<'<'<<XmlObject::element<<'>'<<name<<"</"<<XmlObject::element<<'>';
	strm=tmp.str();
	return strm;
}

void XmlObject_string::from_xml(ifstream& File)
{
	int j=0;
	char c=0;
	string tmp='<'+element+'>';
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}
	for(c=0; File>>c && c!='<';++j)
		tmp[j]=c;
	tmp[j]='\0';
	tmp.resize(j);
	name=tmp;
	tmp="</"+element+'>';
	for(int i=1;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}

}

string XmlObject_string::ret_elem()
{
	return XmlObject::element;
}

void XmlObject_string::set_elem(string xelem)
{
	XmlObject::set_elem(xelem);
}

ifstream& operator >>(ifstream& File, XmlObject_string& x)
{
	if(!File.is_open())
		cerr<<"File not open";
	x.from_xml(File);
	return File;
}


ofstream& operator <<(ofstream& File, XmlObject_string x)
{
	if(!File.is_open())
		cerr<<"File not open";
	File<<x.to_xml();
	return File;
}

ostream& operator <<(ostream& os, XmlObject_string x)
{
	os<<x.to_xml();
	return os;
}

XmlObject_int::XmlObject_int(string xelem, int x):XmlObject(xelem), value(x){}

string XmlObject_int::to_xml()
{
	string strm;
	stringstream tmp;
	tmp<<'<'<<XmlObject::element<<'>'<<value<<"</"<<XmlObject::element<<'>';
	strm=tmp.str();
	return strm;
}

void XmlObject_int::from_xml(ifstream& File)
{
	value=0;
	char c=0;
	int j=0;
	string tmp='<'+element+'>';
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}
	tmp.clear();
	for(j=0; File>>c && c!='<';++j)
	{
		tmp[j]=c;
	}
	--j;
	for(int i=0; i<=j; ++i)
	{
		value+=pow(10,(j-i))*((int)tmp[i]-48);
	}
	tmp="</"+element+'>';
	for(int i=1;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}


}

string XmlObject_int::ret_elem()
{
	return XmlObject::element;
}

int XmlObject_int::ret_value()
{
	return value;
}

void XmlObject_int::set_value(int x)
{
	value=x;
}

ifstream& operator >>(ifstream& File, XmlObject_int& x)
{
	if(!File.is_open())
		cerr<<"File not open";
	x.from_xml(File);
	return File;
}

ofstream& operator <<(ofstream& File, XmlObject_int x)
{
	if(!File.is_open())
		cerr<<"File not open";
	File<<x.to_xml();
	return File;
}

ostream& operator <<(ostream& os, XmlObject_int x)
{
	os<<x.to_xml();
	return os;
}

XmlObject_char::XmlObject_char(string xelem, char xmark):XmlObject(xelem), mark(xmark){}

string XmlObject_char::to_xml()
{
	string strm;
	stringstream tmp;
	tmp<<'<'<<XmlObject::element<<'>'<<mark<<"</"<<XmlObject::element<<'>';
	strm=tmp.str();
	return strm;
}

void XmlObject_char::from_xml(ifstream& File)
{

	char c=0;
	string tmp='<'+element+'>';
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}
	File>>mark;
	tmp="</"+element+'>';
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}
}

string XmlObject_char::ret_elem()
{
	return XmlObject::element;
}

ifstream& operator >>(ifstream& File, XmlObject_char& x)
{
	if(!File.is_open())
		cerr<<"File not open";
	x.from_xml(File);
	return File;
}

ofstream& operator <<(ofstream& File, XmlObject_char x)
{
	if(!File.is_open())
		cerr<<"File not open";
	File<<x.to_xml();
	return File;
}

ostream& operator <<(ostream& os, XmlObject_char x)
{
	os<<x.to_xml();
	return os;
}

XmlVect::XmlVect(string xelem, string elem_list)
					:XmlObject(xelem){}


XmlVect::~XmlVect()
{}


void XmlVect::set_elem(string xelem, string elem_list)
{
	element=xelem;
	if(!tab.empty())
		for(vector<XmlObject_string>::iterator it=tab.begin(); it!=tab.end(); ++it)
		{
			it->set_elem(elem_list);
		}
}

string XmlVect::ret_elem()
{
	return element;
}

void XmlVect::push(XmlObject_string no)
{
	tab.push_back(no);
}


void XmlVect::remove()
{
	tab.pop_back();
}


string XmlVect::to_xml()
{
	stringstream tmp;
	tmp<<"<"+element+">";
	tmp<<"<SIZE>"<<tab.size()<<"</SIZE>";
	for(vector<XmlObject_string>::iterator it=tab.begin(); it!=tab.end(); ++it)
	{
		tmp<<it->to_xml();
	}
	tmp<<"</"+element+'>';
	string output=tmp.str();
	return output;
}


void XmlVect::from_xml(ifstream& File)
{
	char c=0;
	string tmp='<'+element+'>';
	XmlObject_int size("SIZE");
	XmlObject_string myfriend("friend", "\0");
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}
	size.from_xml(File);
	tab.clear();
	for(int j=0; j<size.ret_value(); ++j)
	{
		myfriend.from_xml(File);
		tab.push_back(myfriend);
	}
	tmp="</"+element+'>';
	for(int i=0;i<tmp.length() && File>>c;i++)
	{
		if(tmp[i]!=c)
		{
			cerr<<"Blad pliku. Niepoprawny Xml.Element: "<<element<<endl;
			return;
		}
	}


}
