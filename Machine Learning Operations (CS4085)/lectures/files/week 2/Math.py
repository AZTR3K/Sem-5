class Math:
    def __init__(self,a1,b1=-1,c1=-1):
        self.__var1=a1
        self.__var2=b1
        self._var3=c1
    def add(self):
        c=self.__var1+self.__var2+self._var3
        print("Add= ",c)
class Vector(Math):
    def __init__(self,a,b,c):
        Math.__init__(self,a,b,c)
        # super().__init__(a,b,c)
    def add(self):
        print("Vector class add")
        Math.add(self)
    def __str__(self):
        return "Math object"