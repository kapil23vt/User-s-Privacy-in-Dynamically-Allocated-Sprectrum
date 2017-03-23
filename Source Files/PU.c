#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include <time.h>
#include "declaritions.h"

mpz_t * PU_i_update(struct Pos_Value *pv, paillier_public_key *pub){
  
    int l, h, f;
    mpz_t *T_i = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    mpz_t *T_i_encrypted = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    initialize_mpz_array(T_i_encrypted, 0);
    initialize_mpz_array(T_i, 0);
    int PU_add_grid_count = ceil(L*H*(float)PU_privacy_level/100);
    
    if (PU_add_grid_count > 0){
    PU_add_grid_count = PU_add_grid_count - 1;
    }
    
    int temp_loop;
    int temp_holder;
    int temp_offset_holder;
    int random_value;
    
    for(l = 0; l < L; l++){               
        for(h = 0; h < H; h++){
            for(f = 0; f < F; f++){               
                if (offset(l,h,f)==pv->pos){
                    mpz_t temp, W, V, WplusZ, tempZ, tempone;
                    mpz_set_ui(tempone, 1);
                    
                    mpz_inits(temp, W, V, WplusZ, tempZ, NULL);
                    mpz_setbit (tempZ, K-1);
                    mpz_sub(tempZ,tempZ,tempone);
                    //tempZ = tempZ - 1;
                    gmp_printf("\nValue of tempZ is %Zd",tempZ);
                    mpz_setbit (temp, PSI+K); //set 60+220=280th bit to the right as 1
                    gmp_printf("\nValue of temp is %Zd",temp);
                    mpz_set_ui(V, pv->value);
                    gmp_printf("\nValue of V is %Zd",V);
                    mpz_add(WplusZ, temp, V);
                    gmp_printf("\nValue of temp+V is %Zd",WplusZ);
//                    gmp_printf("%Zd\n%Zd\n%Zd",V,temp,WplusZ);
                    //gmp_printf("\nValue of Z is %Zd",Z);
                    
                    //mpz_sub(W,WplusZ,Z);
                    mpz_sub(W,WplusZ,tempZ);
                    gmp_printf("\nValue of W is %Zd",W);  
                    mpz_init_set(*(T_i+offset(l,h,f)), W);
//                    gmp_printf("%Zd\n",W);
                    mpz_clears(temp, W, V, WplusZ, Z, tempZ, NULL);
                }
                else
                {
                    mpz_init_set_ui(*(T_i+offset(l,h,f)), 0);
                }
                //mpz_init(*(T_i_encrypted+offset(l,h,f)));
                //mpz_init_set_ui(*(T_i_encrypted+offset(l,h,f)), 0);
                //gmp_printf("\nT_i_encrypted is %Zd",*(T_i_encrypted+offset(l,h,f)));
                
                mpz_t temp_zero1; //creating temp_zero variable
                mpz_inits(temp_zero1, NULL);
                temp_holder = l;
                int temp_result = mpz_cmp (*(T_i+offset(l,h,f)),temp_zero1);
                temp_holder = l;
                //printf("\nCurrent index number is %d", offset(l,h,f));
                
                if(temp_result != 0)
                {
                    int x = offset(l,h,f);
                    
                    for (temp_loop = 0; temp_loop <= (PU_add_grid_count); temp_loop++)
                    {
                        x = x%(L*H);
                        printf("\nDoing the Encryption for grid index %d", x);
                        gmp_printf("\n T_i value is %Zd", *(T_i+x));
                        paillier_encrypt(*(T_i_encrypted+x), *(T_i+x), pub);
                        //printf("\nValue after the Encryption = %Zd", *(T_i_encrypted+offset(x,h,f)));
                        x = x+1;
                    }
                 }
                
                l = temp_holder;//gets the value back after exiting the loop
                
                //printf("\nThe value of l after coming out of the encryption part is %d", l);
            }
        }
    }
    return T_i_encrypted;
}

struct Pos_Value* PU_data_generation_coordination(){//randomized data
    
    struct Pos_Value* pv = (struct Pos_Value *) malloc(sizeof(struct Pos_Value)*PU_NUM);
    srand(time(NULL));
    
    int *value=generate_random_array_no_reps(F*H*L, 0, PU_NUM);     
    
//    int *value=(int *)malloc(2*sizeof(int));
//    *(value)=0;
//    *(value+1)=4;
    
    int pu_i;
    for( pu_i=0; pu_i<PU_NUM; pu_i++ ){
        (*(pv + pu_i)).pos = *(value+pu_i);        
        (*(pv + pu_i)).value = rand()%(MAX_SENSITIVITY-MIN_SENSITIVITY)+MIN_SENSITIVITY;
        //(*(pv + pu_i)).value = 20001;
        //(*(pv + pu_i)).value = (*(pv + pu_i)).value/1000;
        printf("PU operation position: %d, inference sensitivity threshold: %ld\n",(*(pv + pu_i)).pos,  (*(pv + pu_i)).value);
    }
    return pv;
}

