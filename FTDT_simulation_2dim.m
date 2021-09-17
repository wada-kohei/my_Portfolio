%円形膜の2次元FTDTシミュレーションプログラム
clear

%パラメータの設定
lx = 0.1;    %x軸方向の大きさ(m)
ly = 0.1;    %y軸方向の大きさ(m)
dx = 1e-3;   %x軸方向の距離刻み(m)
dy = 1e-3;   %y軸方向の距離刻み(m)

T = 0.01;    %計算時間(s)
dt = 1e-5;   %時間刻み(s)
c = 70;      %音速(m/s)

nx = round(lx/dx) + 1;  %x軸方向の配列の数
ny = round(ly/dy) + 1;  %y軸方向の配列の数
nt = round(T/dt) + 1;   %時間軸方向の配列の数

z = zeros(nx,ny,nt); %変位をｚとする
old_z = zeros(nx,ny); %1つ前の時間ステップの変位
now_z = zeros(nx,ny); %現在の時間ステップの変位
new_z = zeros(nx,ny); %1つ次の時間ステップの変位

%lはleft、rはright、uはup、dはdownの略であり、c（center）の左右上下を表す。
x_l = 1:nx-2; %x-1のベクトルの生成
x_c = 2:nx-1; %xのベクトルの生成
x_r = 3:nx;   %x+1のベクトルの生成
y_u = 1:ny-2; %y-1のベクトルの生成
y_c = 2:ny-1; %yのベクトルの生成
y_d = 3:ny;   %y+1のベクトルの生成

%メッシュの設定
[X Y] = meshgrid(-(nx-1)/2:(nx-1)/2,-(ny-1)/2:(ny-1)/2); %(0,0)を中心とした正方形メッシュ

%初期条件の設定
sig = 5; %標準偏差
z(:,:,1) = exp(-((X-10).^2+(Y-20).^2) / (2 * sig^2)); 

%境界条件の適用
%1辺0.1mの正方形メッシュの中に、直径0.1mの円形膜を作る
for y = 1:101
    for x = 1:101
        if((x-51)^2+(y-51)^2 >= 2500)
            z(x,y,1)=0;
        end
    end 
end

z(:,:,2) = z(:,:,1); %初期条件から静かに離す。

old_z = z(:,:,1);
now_z = z(:,:,2);

%FT-TD法の実行
for t=2:nt-1 
    %差分方程式
    %ただし、dx=dyを仮定する。
    K=(c*dt/dx)^2;
    new_z(x_c,y_c) = 2*now_z(x_c,y_c) - old_z(x_c,y_c) + K * (now_z(x_r,y_c) + now_z(x_l,y_c) + now_z(x_c,y_u) + now_z(x_c,y_d) - 4*now_z(x_c,y_c));
    
    %境界条件の適用　直径0.1 mの円形境界の外部の値を常に0とする。
    for y = 1:101
        for x = 1:101
            if((x-51)^2+(y-51)^2 >= 2500)
                new_z(x,y)=0;
            end
        end
    end
    
    %now_z,old_zの更新
    old_z = now_z;
    now_z = new_z;
    %計算結果の格納
    z(:,:,t+1) = new_z;
end

%アニメーション用
for t=1:nt
    mesh(X,Y,z(:,:,t));
    zlim([-1 1])
    xlabel('x axis [mm]')
    ylabel('y axis [mm]')
    zlabel('Displacement')
    F = getframe;
end
