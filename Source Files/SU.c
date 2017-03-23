#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"
#include <stdbool.h>

mpz_t * gen_req(paillier_public_key *pub){
    
    int h, l, f;
    srand(time(NULL));
    int i; int j;int p;
    bool check_vector[total_grid_count];
    bool check_vector2[total_grid_count];
    bool check_vector3[total_grid_count];
    
    mpz_t *R = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));   
    mpz_t *R_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));    
    
    initialize_mpz_array(R, 0);  
    initialize_mpz_array(R_enc, 0);
    
    //int required[] = {0,1,2,3,4,5,6,7};
    //int required[] = {3,4,5,6,7};
    int required[] = {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 72, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 104, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 147, 151, 152, 153, 154, 155, 156, 157, 158, 159, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 221, 222, 223, 224, 225, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 256, 257, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 538, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556 ,557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574, 575, 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 607};
    
    int sizeofarray = sizeof(required)/sizeof(required[0]);
    printf("\nSize of the array is %d", sizeofarray);
    
    //int pos = get_pos(sizeofarray);
    int pos = required[rand()%sizeofarray];
    int tx_power = get_tx_power();
    int SU_privacy_level = get_privacy();
    
    int extragrids = ceil((float)sizeofarray*(float)SU_privacy_level/100);
    extragrids = extragrids - 1;
    printf("\nextragrids is %d", extragrids);
    int location = 0;
    int count = 0;
    
    //int actual_grid_count = ceil((float)total_grid_count*(float)SU_privacy_level/100);
    //int not_required[] = {0,1};
    
    printf("\nSU operation position: %d, transmit power: %d privacy level: %d\n", pos, tx_power, SU_privacy_level);
    for (i=0;i<total_grid_count;i++){
        check_vector[i] = true;
        }
    for (i=0;i<total_grid_count;i++){
        check_vector2[i] = false;
        }
    check_vector2[pos] = true;
    
    for (i=0;i<total_grid_count;i++){
        check_vector3[i] = false;
        }
    check_vector3[pos] = true;
    
    int required_temp[sizeofarray-1];
    int temp_i; int temp_j = 0; int temp_x;
    
    for (temp_i = 0; temp_i< sizeofarray; temp_i++)
    {
        if (pos!= required[temp_i])
        {
            required_temp[temp_j] = required[temp_i];
            temp_j++;
        }
    }
    while(count < extragrids)
    {
        temp_x = rand()%(sizeofarray-1);
        if(required[temp_x]!=pos)
        {
            printf("\nSelected index is %d", temp_x);
            check_vector3[required_temp[temp_x]] = true;
            count++;
        }
    }
    
    
    
    //select extragrids values from the array
    //make sure they are not equal to required[pos]
    int x;
    for (x = 0; x<sizeofarray; x++)
    {
        if (required[x]!=pos && count <extragrids)
        {
            check_vector2[required[x]] = true;
            count++;
        }
    }
   mpz_set_ui(*(R + pos), tx_power);
    
    printf("\nNow Check Vector is \n");
    for ( j =0;j< total_grid_count;j++){
            //printf("\nThis");
        if(check_vector2[j])
        { 
            printf("1 ");
        }
        else{ 
            printf("0 ");
        } 
    }
    printf("\nNow Check Vector3 is \n");
    for ( j =0;j< total_grid_count;j++){
            //printf("\nThis");
        if(check_vector3[j])
        { 
            printf("1 ");
        }
        else{ 
            printf("0 ");
        } 
    }
    
    for(l = 0; l < L; l++){
        for(h = 0; h < H; h++){
                 for(f = 0; f < F; f++){
                     if(check_vector3[l])
                     {
                         paillier_encrypt(*(R_enc + offset(l,h,f)), *(R + offset(l,h,f)), pub);
                     }
                 }
        }
    }
    
    printf("\nclearing all the values of R");
    for(l = 0; l < L; l++){   
         for(h = 0; h < H; h++){
              for(f = 0; f < F; f++){
                  mpz_clear(*(R + offset(l,h,f)));
              }
         }
     }
    
    return R_enc;
    
}


int get_tx_power(){
//    srand(time(NULL));  
//    int tx_power = rand()%1000;     // unit: mWatt
//    return tx_power;
    return 1000;
}

int get_privacy(){
    //write some code to return random values of privacy
    //int r = rand() % 100;
    return 100;
}

mpz_t * generate_U(bool availability, mpz_t *F_enc, paillier_public_key *pub){
    mpz_t *U_enc = (mpz_t *)malloc(L*H*F*sizeof(mpz_t));
    
    int h, l, f;
    if (availability == true){
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    mpz_init(*(U_enc+offset(l,h,f)));
                    paillier_encrypt(*(U_enc+offset(l,h,f)), ZERO, pub);
                    paillier_homomorphic_add(*(U_enc+offset(l,h,f)), *(U_enc+offset(l,h,f)), *(F_enc+offset(l,h,f)), pub); // to calculate time cost
                }
            }
        }
    }
    else{
        for(l = 0; l < L; l++){               
            for(h = 0; h < H; h++){
                for(f = 0; f < F; f++){
                    mpz_init(*(U_enc+offset(l,h,f)));
                    paillier_encrypt(*(U_enc+offset(l,h,f)), ZERO, pub);
                }
            }
        }
    }
    return U_enc;
}