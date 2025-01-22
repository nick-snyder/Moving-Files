
% Write-up (Battle.m)
% My animation starts with translations from the pokemon trainer and the 
% pokeballs on the left and right side of the screens. These translations 
% are a simple loop that adds or subtracts a 1 to the first row of the 
% matrix as many times as necessary (if statements help to keep everything 
% in the same loop). These two images then move out of the screen using 
% the same method and the healthbars of both pokemon move into the scene 
% with the same method. Then a pokeball is thrown into the scene by using 
% rotation along the origin, this pokeball is then morphed into charmander. 
% The pokemon then uses tackle, and this is shown with a translation toward 
% the opposing pokemon, pidgey. That pokemon then moves back, and to 
% simulate a knockback the image is moved back using translations and it is 
% also shrunk to 80% of its size so that it looks like it is further away. 
% The health bar of pidgey then is shrunk to zero by using a morph. And 
% it ends. The text used at the bottom of the screen uses matlab’s 
% text(x, y, text) function, and it is erased by plotting the previous 
% text in white.                                        
%                                                   - Kevin Guzman Velez

function out = Battle(watermark)

    %Part A
    textbox = imread('imgemptytextbox.jpg');
    pokemon1 = imread('imgpokemon-trainer.jpg');
    pokemon2 = imread('imgwildpokemon.jpg');
    charmander = imread('imgcharmander.jpg');
    healthbar1 = imread('imgtrainerpokemonhealthbar.jpg');
    pokeball = imread('pokeball.jpg');
    healthbar2 = imread('imghealthbar2.jpg');
    healthbar1b = imread('imghealthbar1.jpg');
    bar = imread('bar.jpg');
    emptybar = imread('emptybar.jpg');
    
    
    
    
    textbox = Jpeg2pointsConverter(textbox, 75); 
    pokemon1 = Jpeg2pointsConverter(pokemon1, 100); 
    pokemon2 = Jpeg2pointsConverter(pokemon2, 100); 
    healthbar1 = Jpeg2pointsConverter(healthbar1, 110); 
    pokeball = Jpeg2pointsConverter(pokeball, 100);
    healthbar2a = Jpeg2pointsConverter(healthbar2, 100); 
    charmander = Jpeg2pointsConverter(charmander, 100); 
    healthbar1b = Jpeg2pointsConverter(healthbar1b, 100); 
    bar = Jpeg2pointsConverter(bar, 100);
    healthbar2 = [healthbar2a, bar];
    emptybar = Jpeg2pointsConverter(emptybar, 100);
    hText = text(8, 28, 'Wild Pidgey Has appeared', 'FontSize', 10);
    emptybar(2, :) = emptybar(2, :) - 17;
    
    vector = [80; 138];
    matx = ones(1, 143);
    matx = vector*matx;
    emptybar = [emptybar, matx];
    
    vector = [2; 2];
    matx = ones(1, 588);
    matx = vector*matx;
    pokeball = [pokeball, matx];
    
    
    
    pokemon1(1, :) = pokemon1(1, :) - 65;
    pokemon1(2, :) = pokemon1(2, :) - 16;
    healthbar1(1, :) = healthbar1(1, :) + 96;
    textbox(2, :) = textbox(2, :) - 16;
    healthbar1(2, :) = healthbar1(2, :) - 16;
    healthbar2(2, :) = healthbar2(2, :) - 16;
    pokemon2(2, :) = pokemon2(2, :) - 16;
    
    
    hold on;
    axis([0 160 0 144]);
    %plot(Start(1,:),Start(2,:),'k.')
    plot(textbox(1,:),textbox(2,:),'k.')
    plot(pokemon1(1,:),pokemon1(2,:),'k.')
    plot(pokemon2(1,:),pokemon2(2,:),'k.')
    plot(healthbar1(1,:),healthbar1(2,:),'k.')
    watermark(1, :) = watermark(1, :) + 125;
    plot(watermark(1,:),watermark(2,:),'k.')
    
    
    pause(3);
    
    %intro translations
    for d=0:192
    
    plot(textbox(1,:),textbox(2,:),'w.')
    plot(pokemon1(1,:),pokemon1(2,:),'w.')
    plot(pokemon2(1,:),pokemon2(2,:),'w.')
    plot(healthbar1(1,:),healthbar1(2,:),'w.')
    
        if(d < 65)
            pokemon1(1, :) = pokemon1(1, :) + 1;
        end
    
        if(d < 96)
            healthbar1(1, :) = healthbar1(1, :) - 1;
        end
        
        if(d > 96)
            pokemon1(1, :) = pokemon1(1, :) - 1;
            healthbar1(1, :) = healthbar1(1, :) + 1;
        end
    
        plot(textbox(1,:),textbox(2,:),'k.')
        plot(pokemon1(1,:),pokemon1(2,:),'k.')
        plot(pokemon2(1,:),pokemon2(2,:),'k.')
        plot(healthbar1(1,:),healthbar1(2,:),'k.')
        pause(.01);
    
        if(d == 96)
            pause(2.5);
        end
       
    end
    
    
    plot(pokeball(1, :), pokeball(2, :), 'k.')
    pokemon1 = charmander;
    pokemon1(2, :) = pokemon1(2, :) - 16;
    healthbar1 = healthbar1b;
    healthbar1(2, :) = healthbar1(2, :) - 16;
    healthbar1(1, :) = healthbar1(1, :) + 88;
    healthbar2(1, :) = healthbar2(1, :) - 89;
    
    
    plot(pokemon2(1,:),pokemon2(2,:),'k.')
    plot(healthbar1(1,:),healthbar1(2,:),'k.')
    plot(healthbar2(1, :), healthbar2(2, :), 'k.')
    
    %healthbars in
    for x=0:89
        plot(healthbar1(1,:),healthbar1(2,:),'w.')
        plot(healthbar2(1, :), healthbar2(2, :), 'w.')
        healthbar1(1, :) = healthbar1(1, :) - 1;
        healthbar2(1, :) = healthbar2(1, :) + 1;
        plot(healthbar1(1,:),healthbar1(2,:),'k.')
        plot(healthbar2(1, :), healthbar2(2, :), 'k.')
        pause(.01);
    end
    
    hText = text(8, 28, 'Wild Pidgey Has appeared', 'FontSize', 10, 'Color','w');
    pause(.1);
    hText = text(8, 28, 'Go Charmander!', 'FontSize', 10, 'Color','k');
    
    %rotation animation
    rotation = [cos(pi/36) sin(pi/36); -sin(pi/36) cos(pi/36)];
    pokeball(1, :) = pokeball(1, :) - 11;
    pokeball(2, :) = pokeball(2, :) + 68;
    for x = 0:6
    plot(pokeball(1, :), pokeball(2, :), 'w.')
    pokeball = rotation * pokeball;
    plot(pokeball(1, :), pokeball(2, :), 'k.')
    pause(.01);
    end
    
    for i = 0:1/8:1
        plot(pokeball(1, :), pokeball(2, :), '.w');
        pokeball = (1 - i) * pokeball + i * pokemon1;
        plot(pokeball(1, :), pokeball(2, :), '.k');
        pause(.01);
    end
    hText = text(8, 28, 'Go Charmander!', 'FontSize', 10, 'Color','w');
    hText = text(8, 28, 'Charmander use Tackle!', 'FontSize', 10, 'Color','k');
    
    pause(3);
    rescale = [.8 0; 0 .8];
    for i = 0:29
        plot(pokeball(1, :), pokeball(2, :), '.w');
        plot(textbox(1,:),textbox(2,:),'w.');
        plot(pokemon2(1, :), pokemon2(2, :), '.w');
    
    
        if(i < 14)
            pokeball(1, :) = pokeball(1, :) + 1;
            pokeball(2, :) = pokeball(2, :) + 1;
        end
        if(i == 14)
            pokemon2(1, :) = pokemon2(1, :) - 120;
            pokemon2(2, :) = pokemon2(2, :) - 100;
            pokemon2 = rescale * pokemon2;
            pokemon2(1, :) = pokemon2(1, :) + 125;
            pokemon2(2, :) = pokemon2(2, :) + 105;
        end
    
        if(i == 28)
            rescale = [1.1 0; 0 1.1];
            pokemon2(1, :) = pokemon2(1, :) - 125;
            pokemon2(2, :) = pokemon2(2, :) - 105;
            pokemon2 = rescale * pokemon2;
            pokemon2(1, :) = pokemon2(1, :) + 120;
            pokemon2(2, :) = pokemon2(2, :) + 100;
        end
    
        if(i >= 14)
            pokeball(1, :) = pokeball(1, :) - 1;
            pokeball(2, :) = pokeball(2, :) - 1;
        end
        plot(pokeball(1, :), pokeball(2, :), '.k');
        plot(pokemon2(1, :), pokemon2(2, :), '.k');
    
        plot(textbox(1,:),textbox(2,:),'k.')
        pause (.01);
    end
    hText = text(8, 28, 'Charmander use Tackle!', 'FontSize', 10, 'Color','w');
    hText = text(8, 28, 'Tackle was super effective!', 'FontSize', 10, 'Color','k');
    
    healthbar2a(2, :) = healthbar2a(2, :) - 16;
    for i = 0:1/8:1
        plot(healthbar2(1, :), healthbar2(2, :), '.w');
        plot(bar(1, :), bar(2, :), '.w');
        plot(healthbar2a(1, :), healthbar2a(2, :), '.w');
        bar = (1 - i) * bar + i * emptybar;
        plot(healthbar2a(1, :), healthbar2a(2, :), '.k');
        plot(bar(1, :), bar(2, :), '.k');
        pause(.01);
    end
    
    hText = text(8, 28, 'Tackle was super effective!', 'FontSize', 10, 'Color','w');
    hText = text(8, 28, 'Charmander won!', 'FontSize', 10, 'Color','k');
    hText = text(8, 28, 'Charmander won!', 'FontSize', 10, 'Color','w');
    pause(2);
    hText = text(8, 28, 'Thanks for Watching!', 'FontSize', 10, 'Color','k');
    
    hold off;
    out = watermark;
  
end
