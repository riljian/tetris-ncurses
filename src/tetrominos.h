#ifndef tetrominos_h
#define tetrominos_h

#define height 20
#define width 20
#define ptrr ptr->range[i]

struct Range{
	int y, x;
	char c;
};

class cube{
	friend class tetrisBoard;
	friend cube& operator>>(cube&, int);
	friend cube& operator<<(cube&, int);
	public:
		cube& drop();
		cube& up();
		void operator=(cube*);
		virtual cube& operator+(int)=0;
		virtual void setCube()=0;
		struct Range range[8];
	protected:
		int degree;
};

class shadowCube:public cube{
	friend class tetrisBoard;
	public:
		shadowCube();
		cube& operator+(int i){}
		void setCube(){}
};

class Icube:public cube{
	friend class tetrisBoard;
	public:
		Icube(){setCube();}
		void setCube();
		Icube& operator+(int);
};

class Ocube:public cube{
	friend class tetrisBoard;
	public:
		Ocube(){setCube();}
		void setCube();
		Ocube& operator+(int n){}
};

class Scube:public cube{
	friend class tetrisBoard;
	public:
		Scube(){setCube();}
		void setCube();
		Scube& operator+(int);
};

class Zcube:public cube{
	friend class tetrisBoard;
	public:
		Zcube(){setCube();}
		void setCube();
		Zcube& operator+(int);
};

class Tcube:public cube{
	friend class tetrisBoard;
	public:
		Tcube(){setCube();}
		void setCube();
		Tcube& operator+(int);
};

class Lcube:public cube{
	friend class tetrisBoard;
	public:
		Lcube(){setCube();}
		void setCube();
		Lcube& operator+(int);
};

class Jcube:public cube{
	friend class tetrisBoard;
	public:
		Jcube(){setCube();}
		void setCube();
		Jcube& operator+(int);
};

#endif
