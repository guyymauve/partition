fs=44100; %frequence d'echantillonage (Hz)
nbit=16;   % nombre de bits par echantillon
mode=2;   %pour dire stéreo
D=5;        % durée d'enregistrement (s)
wavefile='C:\Users\bapti\Documents\MATLAB\test.wav';
nNote=0;
ficres='C:\Users\bapti\Documents\Code_Blocks\PartitionF\bin\Debug\Notes.txt';
fid=fopen(ficres,'wt');  % ouverture du fichier
fprintf(fid, '%s', 'D 4 4 120');
maxi_seuil = 0;

enregistrement=audiorecorder(fs,nbit, mode);
recordblocking(enregistrement, D);
%parole= play(enregistrement);
y=getaudiodata(enregistrement);
audiowrite(wavefile,y,fs);

dureeSample = 0.5;

nbrZU = D / dureeSample; %J'aimerais remercier ma famille et mes amis pour m'avoir 
               %aidé à écrire cette ligne de code.

for bocle=0:(nbrZU - 1)
    sond2 = y((bocle*fs*D/nbrZU)+1:(bocle+1)*fs*D/nbrZU);
    sond = sond2';
    fmaxi=0;
    maximum=0;
    [N,p]=size(sond);
    y_piste=sond(:,1);
    t=(0:N-1)/fs;
    plot(t,y_piste);
    %hold on;
    figure;
    z=fft(y_piste);
    f=(0 :N-1)/N*fs;
    plot(f,abs(z));
    %detection du maximum = fondamental
    maximum=abs(z(1));
    maxi=1;
    for i=2:N/2
        if abs(z(i))> maximum 
                maximum =abs(z(i));
                maxi=i;
        end
    end
    fmaxi=(maxi-1)/N*fs;
    
    if bocle ~= 0
        affm1 = afficher;
    end
    
    afficher=floor(fmaxi);
    
    if afficher >= 32.7 && afficher <= 61.74
        ecart = 1.32;
    elseif afficher >= 61.74 && afficher <= 123.47
        ecart = 2.6;
    elseif afficher >= 123.47 && afficher <= 246.94
        ecart = 5.3;
    elseif afficher >= 249.94 && afficher <= 493.88
        ecart = 10.6;
    elseif afficher >= 493.88 && afficher <= 987.77
        ecart = 21.1;
    elseif afficher >= 987.77 && afficher <= 2000
        ecart = 42;
    end
    
    if bocle == 0
        affm1 = afficher;
    end
    
    if bocle == 0
        dureeNote = dureeSample;
    elseif (afficher >= affm1 - ecart) && (afficher <= affm1 + ecart)
        dureeNote = dureeNote + dureeSample;
    end
    
    if dureeNote > 6.75
        dureeNote = 6.75;
    end
    
    if (afficher <= affm1 - ecart) || (afficher >= affm1 + ecart) % Ajouter intervalle
        dureeTotale = dureeNote * 1000;
        fprintf(fid,'\n%s %d %d %s', 'M', affm1, dureeTotale, '40'); %écriture de la note
        nNote=nNote+1;
        dureeNote = dureeSample;
    end
    
    if bocle == nbrZU - 1
        dureeTotale = dureeNote * 1000;
        fprintf(fid,'\n%s %d %d %s', 'M', afficher, dureeTotale, '40'); %écriture de la note
        nNote=nNote+1;
    end

    display(fmaxi);% affichage de la frequence de la note
    %fmaxi=(maxi-1)/N*fs;% calcul de la frequence du fondamental
    %display(fmaxi);% affichage de la frequence de la note
    % calcul de la frequence du maximum
                           % le maximum est-il le fondamental ou le premier
                           % harmonique ?
     seuil=abs(z(maxi))/25;
     i=1;   %int32(32*N/fs)+1;
    while (abs(z(i))< seuil) && (i < 3*maxi/4) 
                i=i+1;
    end
    maximum1=abs(z(i));
    if i< 3*maxi/4
        while ((abs(z(i))> abs(z(maxi))/75)) && (i < 3*maxi/4) 
                i=i+1;
                if abs(z(i)) > maximum1
                            maximum1=abs(z(i));
                            maxi_seuil=i;
                end
        end
        maxi=maxi_seuil;
    end


    fmaxi=double((maxi-1)*fs/N);

    display(fmaxi);% affichage de la frequence de la note
end

figure;
[N,p]=size(y);
y_piste=y(:,1);
t=(0:N-1)/fs;
plot(t,y_piste);

M=max(y_piste);
m=min(y_piste);
etendue = M-m;
intervalle = 0.1*etendue;
vx = [];
portee = 4410;

for o=2:length(t)-1
    if o <= portee
        opp = o + portee;
        opm = o + 1;
        omm = o - 1;
        omp = 1;
    elseif o > length(t)-portee
        opp = length(t);
        opm = o + 1;
        omm = o - 1;
        omp = o - portee;
    else
        opp = o + portee;
        opm = o + 1;
        omm = o - 1;
        omp = o - portee;
    end
    
    if (((y_piste(o)) > (max(y_piste(opm:opp)))) && ((y_piste(o)) > (max(y_piste(omp:omm)))))
        if y_piste(o) > intervalle
            vx = [vx t(o)];
        end
    end
end

display(vx);

vx2 = [];

for j=1:length(vx)-1
    vx2 = [vx2 vx(j+1)-vx(j)];
end

display(vx2);

noire = mean(vx2);
noire = round(10*noire)/10;
bpm = 60/noire;

%sound(y, fs);

status=fclose(fid); %fermeture du fichier 
system('test.bat');
