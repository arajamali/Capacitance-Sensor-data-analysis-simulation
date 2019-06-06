clc;
clear;
close all;

%% Load Data
%data=load('Ls_H_LLS');
data=load('RayData');
%data=load('LF_H_LTB');
 x=data.x

%%x=CreateData1(5000);

%% K-Means Settings

nCluster=2;                              % Number of Clusters

DistanceMetric='cityblock';            % Metric

Options  = statset('Display','final');


%% Run K-Means

[I C  sumd D]=kmeans(x,nCluster,...
    'Distance',DistanceMetric,...
    'Options',Options);

%% Plot results

Cluster11=[x(I==1,1),x(I==1,2)];
Cluster21=[x(I==2,1),x(I==2,2)];
Cluster3=[x(I==3,1),x(I==3,2)];
figure;
plot(x(I==1,1),x(I==1,2),'b.');
hold on;
plot(x(I==2,1),x(I==2,2),'r.');

plot(x(I==3,1),x(I==3,2),'g.');

%plot(C(:,1),C(:,2),'kx','LineWidth',2,'MarkerSize',14);
hold off



%plot(C(:,3),C(:,4),'kx','LineWidth',2,'MarkerSize',14);


legend('Claster 1','Cluster 2','Cluster 3','Cluster Centers');

xlabel('H_L_L_S');
ylabel('L_s');

hold off;




