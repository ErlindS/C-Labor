#include <robot.h>
#include <math.h>
#include <stdio.h>

//Vorbereitungsaufgabe 6 a
vector_t vector_create(double x, double y){
    vector_t test;
    test.x = x;
    test.y = y;
    return test;
}


color_t color_create(char x, char y, char z){
       color_t Farben;
        Farben.red = x;
        Farben.green = y;
        Farben.blue = z;
        return Farben;
}


struct line{
    vector_t point;
    vector_t direction;
};

typedef struct line line_t;




// Vorbereitungsaufgabe 6 b
vector_t vector_minus(vector_t a, vector_t b){
    return vector_create(
          a.x - b.x
        , a.y - b.y
    );
}

//Vorbereitungsaufgabe 6 c
double vector_length(vector_t r){
    return sqrt(r.x*r.x + r.y*r.y);
}

//Vorbereitungsaufgabe 6 d
double vector_orientation(vector_t r){
    return atan2(r.y, r.x);
}

//Vorbereitungsaufgabe 6 e
vector_t vector_plus(vector_t a, vector_t b){
    return vector_create(a.x+b.x, a.y+b.y);
}

vector_t vector_times(vector_t r, double s){
    return vector_create( r.x*s, r.y*s);
}

double vector_scalar_product(vector_t a, vector_t b){
    return a.x*b.x+a.y*b.y;
}

vector_t vector_orthogonal(vector_t r){
    return vector_create( -1 * r.y ,   r.x);
}


typedef enum{
     CATCHING
    ,MOVE_BALL_A
} state_t;


double linear_interpolation(double x,double x_min, double y_min, double x_max, double y_max){
    double m= (y_max - y_min) / (x_max - x_min);
    double n = y_min - m* x_min;
    return  m * x + n;
}

void kick1(){
    
}

double begrenze(double x, double min, double max) {
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

void advanced_targeting(vector_t B, vector_t Z, vector_t R, double k_1_min, double k_1_max, double k_2_max){
    
    vector_t RB = vector_minus(B, R);
    vector_t BZ = vector_minus(Z, B);
    RB = vector_times(RB, 1/(vector_length(RB)));
    vector_t v_1 = vector_times(BZ, 1/(vector_length(BZ)));
    vector_t v_2 = vector_orthogonal(v_1);
    double cosalpha = vector_scalar_product(v_1, RB);
     if(cosalpha > 0.97){
//         prepare_kick(0, kick_energy_max());
         k_1_min = 0.1;
     }
//     double k_1 = linear_interpolation(cosalpha, 1, k_1_min, -1, k_1_max);
    //double k_2 = linear_interpolation(cosalpha, 1, 0      , -1, k_2_max);
    double k_1 = linear_interpolation(cosalpha, 1.0, k_1_min, 0.4, k_1_max);
    double k_2 = linear_interpolation(cosalpha, 1.0, 0      , 0.0, k_2_max);
    k_1 = begrenze(k_1, k_1_min, k_1_max);
    k_2 = begrenze(k_2, 0.0    , k_2_max);
    
    if(vector_scalar_product( v_2, RB) < 0){
        k_2 = -k_2;
    }
    // B - v1 * k_1 - v2 * k_2
    // B - (v1 * k_1 + v2 * k_2)
    vector_t P = vector_minus(B, vector_plus(vector_times(v_1, k_1), vector_times(v_2, k_2)));
    P.x = begrenze(P.x, -3.3, 3.3);
    P.y = begrenze(P.y, -2.3, 2.3);
    
    
    double phi = vector_orientation(v_1);
    set_position(P, phi);
    printf("das ist cosalpha %lf\n", cosalpha);
    printf("das ist kick_energy_min %lf\n", kick_energy_min());
    printf("das ist kick_energy_max %lf\n", kick_energy_max());
    printf("das ist kick_energy_max %lf\n", phi);
    
}


struct line_intersection{
  double det;  
  vector_t lambda;  
};

typedef struct line_intersection line_intersection_t;


line_t line_erzeugen(vector_t A, vector_t B){
    line_t C;
    C.point = A;
    C.direction = vector_minus(B, A);
    return C;
}

vector_t line_point_at(line_t line, double lambda){
    return vector_plus(line.point, vector_times(line.direction, lambda));
}

double line_point_lambda(line_t line, vector_t P){
    vector_t v = vector_minus(P, line.point);
    double z = vector_scalar_product(v, line.direction);
    double n = vector_scalar_product(line.direction, line.direction);
    return z/n;
}

double line_point_distance(line_t line, vector_t P){
    double lambda = line_point_lambda(line, P);
    vector_t F = line_point_at(line, lambda);
    vector_t d = vector_minus(P,F);
    return vector_length(d);
};


line_intersection_t line_intersection_erzeuge(line_t G, line_t H){
    line_intersection_t L;
    vector_t g_n = vector_orthogonal(G.direction);
    vector_t h_n = vector_orthogonal(H.direction);
    vector_t w = vector_minus(H.point, G.point);
    L.det = vector_scalar_product(G.direction, h_n);
    L.lambda.x = vector_scalar_product(h_n , w) * 1/L.det;
    L.lambda.y =  vector_scalar_product(g_n , w) * 1/L.det;     
    return L;
}
/*
void Torwart2(){
    while(1){
        ball_t Ball = ball();
        vector_t A = vector_create(-2.75, 0.25);  
        vector_t B = vector_create(-2.75, -0.25);
        vector_t C = vector_create(3, 0);
        vector_t D = Ball.position;
        
        line_t g = line_erzeugen(A,B);
        line_t h = line_erzeugen(C,D);
        line_intersection_t L = line_intersection_erzeuge(g,h);
        vector_t S_G;
        vector_t S_H;
        
        S_G = line_point_at(g, L.lambda.x);
        S_H = line_point_at(h, L.lambda.y);
        
        printf("das ist S_G.x%lf\n", S_G.x);
        printf("das ist S_H.x%lf\n", S_H.x);
        
        printf("das ist S_G.y%lf\n", S_G.y);
        printf("das ist S_H.y%lf\n", S_H.y);
        
        set_position(S_G, 0);
        
    }
}
*/

void schuss(vision_t* vision){
    
        robot_t R = vision->robots[vision->my_index];
        ball_t B= vision->ball;
        static double k_1_min;
        k_1_min = 0.3;
       
        //der Vektor auf den ich spielen werde
        vector_t Z;
        
        //linke Seite aber Oben
        if(B.position.x < 0 && B.position.y > 0){
            Z.x = -1;
            Z.y = 1;
        }
        
        //linke Seite aber Unten
        if(B.position.x < 0 && B.position.y < 0){
            Z.x = -1;
            Z.y = -1;
        }
        
        
        //Rechte Seiter aber Oben
        if(B.position.x > 0 && B.position.y > 0){
            Z.x = 1;
            Z.y = 1;
        }
        
        //Rechte Seiter aber Unten
        if(B.position.x > 0 && B.position.y < 0){
            Z.x = 1;
            Z.y = -1;
        }
        
        prepare_kick(0.9, kick_energy_max());
        //vector_t Z = vector_create(3,their_goal_left());


        advanced_targeting(B.position, Z, R.position, k_1_min, 0.7, -0.7);
}


state_t process_state_catching(vision_t* vision){
        vector_t R = vision->robots[vision->my_index].position;
        vector_t B = vision->ball.position;
        double d = vector_length(vector_minus(R,B));
        vector_t RB;
        vector_t Torwart;
        double k = B.y;
        double phi = atan((B.y - R.y)/(B.x - R.x));
        RB = vector_minus(R, B);
        printf("das ist der Abstand%lf\n", vector_length(RB));

        
        
        if(B.y > 0.35){
            k = 0.35;
        }
        if(B.y < -0.35){
            k = -0.35;
        }
        Torwart = vector_create(-2.875, k);
        set_position(Torwart, phi);
    
    
    if(d < 0.5 ){
        return MOVE_BALL_A;
    }
    return CATCHING;
}

state_t process_state_move_ball_a(vision_t* vision){
//     vector_t T = vector_create(1.0,-1.0);
        vector_t B  = vision->ball.position;
        vector_t R = vision->robots->position;
        double d = vector_length(vector_minus(R,B));

        schuss(vision);
    
    if(d < 0.5 ){
        return MOVE_BALL_A;
    }
    return CATCHING;
    
}


state_t process_state(vision_t* vision, state_t state){
    switch(state){
        default:
        case CATCHING: return process_state_catching(vision);
        case MOVE_BALL_A: return process_state_move_ball_a(vision);
    };
}
vector_t WoDieMeistenGegenersind(vision_t* v){
    vector_t Durchschnitsskoordinate;
    for(int i=0;i < 10;i++){
        Durchschnitsskoordinate.x = v->robots[i].position.x;
        Durchschnitsskoordinate.y = v->robots[i].position.y;
    }
    return Durchschnitsskoordinate;
}

int main() {
     set_team_name("Smurfs");
     set_robot_name("Erlind");
//
//     static color_t schwarz = color_create(0,0,0);
//     schuss();
//     Torwart2();
//     test();
     state_t state = CATCHING;
     while(1){
         vision_t v;
         vision(&v);
         state = process_state(&v, state);
     }

    return 0;

}
