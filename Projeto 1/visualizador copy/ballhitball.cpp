void Visualizador::ball_hit_ball(){
    int hipotenusa;
    int proj_j,vjhip_x,vjhip_y,vjhip_parallel,vjhip_parallel_x,vjhip_parallel_y,vjhip_espelhado,vjhip_espelhado_x,vjhip_espelhado_y,novo_vetor_j,novo_vetor_j_x,novo_vetor_j_y;
    int proj_i,vihip_x,vihip_y,vihip_parallel,vihip_parallel_x,vihip_parallel_y,vihip_espelhado,vihip_espelhado_x,vihip_espelhado_y,novo_vetor_i,novo_vetor_i_x,novo_vetor_i_y;
    // for (int i = 0; i < (bodies.size()); i++){
    //   for (int j = i+1; j < (bodies.size()); j++){
    for (int i = 0; i < (bodies.size()); i++){
      for (int j = i+1; j < (bodies.size()); j++){
        double cateto1 =(bodies[i].x - bodies[j].x);
        double cateto2 = (bodies[i].y - bodies[j].y);
        hipotenusa =  sqrt(pow(cateto1,2)+pow(cateto2,2));
        if (hipotenusa < (bodies[i].radius + bodies[j].radius)){
          printf("Choque de Bolas!");
          
          //BOLA1
          proj_j = (bodies[j].vx*cateto1+bodies[j].vy+cateto2)/(hipotenusa);
          vjhip_x = (proj_j*cateto1)/hipotenusa;
          vjhip_y = (proj_j*cateto2)/hipotenusa;
          
          vjhip_parallel_x = bodies[j].vx-vjhip_x;
          vjhip_parallel_y = bodies[j].vy-vjhip_y;
         
          vjhip_espelhado_x = -(vjhip_x);
          vjhip_espelhado_y = -(vjhip_y);
         
          bodies[j].vx = vjhip_espelhado_x - vjhip_parallel_x;//novo_vetor_j_x
          bodies[j].vy = vjhip_espelhado_y - vjhip_parallel_y;//novo_vetor_j_y

          //BOLA2
          proj_i = (bodies[i].vx*cateto1+bodies[i].vy+cateto2)/(hipotenusa);
          vihip_x = (proj_i*cateto1)/hipotenusa;
          vihip_y = (proj_i*cateto2)/hipotenusa;
          
          vihip_parallel_x = bodies[i].vx-vihip_x;
          vihip_parallel_y = bodies[i].vy-vihip_y;
        
          vihip_espelhado_x = -(vihip_x);
          vihip_espelhado_y = -(vihip_y);
   
          bodies[i].vx = vihip_espelhado_x - vihip_parallel_x;//novo_vetor_i_x
          bodies[i].vy = vihip_espelhado_y - vihip_parallel_y;//novo_vetor_i_y
          if ( (proj_i>0 &proj_j<0)|(proj_i<0 &proj_j>0)){
            proj_i=--proj_i;
            proj_j=-proj_j;
          }
          if((proj_i>0 &proj_j>0)|(proj_i<0 &proj_j<0)){
              proj_j=-proj_j;
          }

          // }
          // else if{

          // }
        }
      }
    }
  }