function []= create_text(C)
   [m,n]=size(C);
   format='%s';
   for i=1:n-1
       format=strcat(format,' %s');
   end
   format=strcat(format,'\n');
   fileID=fopen('clusters.txt','w');
   fileID2=fopen('..\\ADLAS\\clusters.txt','w');
   for i=1:m
       fprintf(fileID,format,C{i,:});
		fprintf(fileID2,format,C{i,:});
   end
end


