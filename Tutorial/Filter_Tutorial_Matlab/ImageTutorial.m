% u,v: image points
% s,t: kernel points
% w: kernel, w(s,t)
% f: source image, f(x,y)

clc; clear all; close all;

% image read
f = imread('Pattern_original_GaussNoise.tif');
f = rgb2gray(f);
[M, N] = size(f);   %  M=500. N=500

% define window
w =[1 1 1 ;  1 1 1 ;  1 1 1];
[wM, wN] = size(w);   % wM=3, wN=3
wSum = sum(w(:));
if(wSum == 0)
    wSum = 1;
end

%Padding
% e.g. 3 x 3 Filter -> pad 1 each side or 2 total
b = (wM - 1) / 2; % b: yPad   % a=1
a = (wN - 1) / 2; % a: xPad   % b=1

% fPad image index: [1 to M+(2*b)] x [1 to N+(2*a)]
fPad = zeros(M+wM-1,N+wN-1);
fPad(a+1:a+M,b+1:b+N) = double(f);

% apply 2D-convolution
gPad = zeros(size(fPad));
tic

for v = b+1:b+M                     % 행
    for u = a+1:a+N                 % 열
        % convolution of kernel at one point (u,v)
        conv = 0;
        for t = -b:b               % 행
            for s = -a:a           % 열
                  conv = conv + ( fPad(v+t,u+s) * w(t+b+1,s+a+1) );
            end
        end
        gPad(v,u) = conv / wSum;
    end
end


g = gPad(b+1:b+M, a+1:a+N); % cropping   -1은 왜 안해 ?
toc

figure, imshow(f)
figure, imshow(uint8(fPad))
figure, imshow(uint8(g))