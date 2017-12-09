function [clusters]=get_cluster(filename)
[Y,app]=xlsread(filename);
m=4;
n=floor(size(Y,1)/4);
app=app(:,1);app(1)=[];
Y(:,2)=Y(:,2)-Y(:,1);
Y=Y';
net = selforgmap([m n]);
net = train(net,Y);
y = net(Y);
classes = vec2ind(y);
classes=classes';
Y=Y';
h=figure;
for a=1:m*n
plot(Y(classes==a,1),Y(classes==a,2),'o');hold on;
end
title('Visualization of datapoints');
xlabel('Start time');
ylabel('Running time');
saveas(h,'cluster_img','jpeg');
k=1;
for i=1:m*n
   for j=1:size(Y,1)
      if(classes(j)==i)
         mat(i,k)=app(j);
         k=k+1;
       end
   end
   k=1;
end
k=1;
[m,n]=size(mat);
for i=1:m
      if(isempty(mat{i,2})==0)   
      set(k,:)=mat(i,:);
      k=k+1;
     end
end
xlswrite('temp1',set);  
[num,set]=xlsread('temp1.xls');
[m,n]=size(set);
count=0;
i=1;
while i<=size(set,1)
  j=1;
  while j<=size(set,1)
     X=setdiff(set(i,:),set(j,:));
     if(isempty(X)==1)
         count=count+1;
     end
     if(size(X,2)==1)
        if(isempty(X{1})==1)
          count=count+1;
        end
     end
     j=j+1;
   end
   final(i)={count};
   i=i+1;
   count=0;
end
for i=1:size(set,1)
set(i,:)=flip(sort(set(i,:)));
end
set(:,n+1)=final;
tab=unique(cell2table(set));
tab=sortrows(tab,n+1,'descend');
clusters=table2cell(tab);
xlswrite('temp2',clusters);
[num]=xlsread('temp2.xls');
for i=1:size(num)
   if(num(i)<2)
      break
   end
end
clusters=clusters((1:i-1),(1:size(clusters,2)-1));
xlswrite('clusters',clusters);
create_text(clusters);
end

