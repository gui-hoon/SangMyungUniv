import pymysql

class MySQLPython:
    # Mysql 연동
    def __init__(self) :
        self.con = pymysql.connect(
            host='localhost',
            user='root',
            passwd='2330514s',
            db='mydb',
            charset='utf8'
        )
        self.cursorObject = self.con.cursor()

    def __del__(self):
        self.con.close()
        print("Exit Program")

    # SELECT
    def select(self, sql):
        self.cursorObject.execute(sql)
        rows = self.cursorObject.fetchall()
        for row in rows:
            print(row)

    # UPDATE
    def update(self, sql):
        self.cursorObject.execute(sql)
        self.con.commit()

    # CLI
    def printCli(self):
        print("========================================================")
        print("(0) 종료")
        print("(1) 릴레이션 생성 및 데이터 추가")
        print("(2) 제목을 이용한 검색")
        print("(3) 관객수를 이용한 검색")
        print("(4) 개봉일을 이용한 검색")
        print("========================================================")
        print("원하는 번호를 입력 하시오")

    # CREATE Relation
    def createRelation(self):
        with open('create_table.txt','r') as f:
            query = f.read()
        self.cursorObject.execute(query)

    # INSERT movie data
    def insertDatas(self):
        with open('movie_data.txt', 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip().split("|")
                sql = "insert into movie values('" + line[1] +"','"+ line[2] +"','"+  line[3] +"','"+ line[4] +"','"+ line[5] +"',"+ line[6]+","+\
                       line[7] +","+ line[8] +",'"+ line[9] + "')"
                print(sql)
                self.cursorObject.execute(sql)
                self.con.commit()

    # Search using the title
    def searchTitle(self, keyword):
        sql = f"select * from movie where title like '%{keyword}%'"
        self.cursorObject.execute(sql)
        rows = self.cursorObject.fetchall()
        for row in rows:
            print(row)

    # Search using the number of audiences
    def searchViewers(self, keyword):
        sql = f"select * from movie where totalnum > {keyword}"
        self.cursorObject.execute(sql)
        rows = self.cursorObject.fetchall()
        for row in rows:
            print(row)

    # Search using the release date.
    def searchReleaseDate(self, date):
        date1, date2 = date.split(',')
        sql = f"select * from movie where DATE(releasedate) between '{date1}' and '{date2}'"
        self.cursorObject.execute(sql)
        rows = self.cursorObject.fetchall()
        for row in rows:
            print(row)


if __name__ == "__main__":
    Dao = MySQLPython()
    # 실습 1을 위해 아래 주석을 제거하고 사용
    # print("실습 #1 - Select")
    # Dao.select("select name from instructor where dept_name = 'Comp. Sci.' and salary>70000")
    # Dao.select("select name, course_id from instructor, teaches where instructor.ID = teaches.ID and instructor.dept_name = 'Biology'")
    #
    # print("\n실습 #2 - Update")
    # print("Before Update")
    # Dao.select("select * from instructor")
    # Dao.update("update instructor set salary=salary*1.05")
    # print("After Update")
    # Dao.select("select * from instructor")

    # 실습 2
    print("실습 #2: 영화 검색 프로그램")
    while True:
        Dao.printCli()
        cli = int(input())
        if cli == 0:
            exit(0)
        elif cli == 1:
            print("Creating a Movie Relation")
            Dao.createRelation()
            print("Insert movie data")
            Dao.insertDatas()
            print("success")
        elif cli == 2:
            print("사용자 입력: ")
            Dao.searchTitle(input())
        elif cli == 3:
            print("사용자 입력: ")
            Dao.searchViewers(int(input()))
        elif cli == 4:
            print("사용자 입력: ")
            Dao.searchReleaseDate(input())
        else:
            print("0, 1, 2, 3, 4중 원하는 번호를 입력 하시오\n")

