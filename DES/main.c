#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
/*
    Inputs
        Key: char array
        plaintext: char array
    Outputs:
        ciphertext: char array
*/
uint64_t PC_1(uint64_t input) {
    uint64_t pc1[] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };
    uint64_t output = 0;
    for(int i=0;i<56;i++)
    {
        output |= (input >> (64- pc1[i]) & 1) << (55-i);
    }
    return output;
}

uint64_t pc_2(uint64_t C,uint64_t D) {
    uint64_t input = (C << 28) | (D);
    uint64_t pc2[] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };
    uint64_t output = 0;
    for(int i=0;i<48;i++)
    {
        output |= (input >> (56- pc2[i]) & 1) << (47-i);
    }
    return output;
}

uint64_t initial_Permutation(uint64_t input) {
    const int IP[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
    };
    uint64_t output = 0;
    for (int i = 0; i < 64; ++i) {
        output |= ((input >> (64 - IP[i])) & 1) << (63 - i);
    }
    return output;
}

uint64_t expansion_permutation(uint64_t input){
    int e_table[] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };
    uint64_t output = 0;
    for (int i = 0; i < 48; ++i) {
        output |= ((input >> (32 - e_table[i])) & 1) << (47 - i);
    }
    return output;
}

uint64_t substitution_choice(uint64_t input){
    int s[8][4][16] = {
        { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
          {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
          {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
          {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} },
        { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
          {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
          {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
          {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} },
        { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
          {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
          {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
          {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} },
        { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
          {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
          {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
          {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} },
        { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
          {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
          {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
          {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} },
        { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
          {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
          {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
          {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} },
        { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
          {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
          {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
          {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} },
        { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
          {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
          {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
          {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} }
    };
    uint64_t output = 0;
    for(int i=0;i<8;i++){
        uint64_t s_input = ((input>>(42-(i*6))) & 0x3f);
        uint64_t s_in1 = (s_input &1) | ((s_input & 0x20)>>4);
        uint64_t s_in2 = (s_input & 0x1E)>>1;
        output |= s[i][s_in1][s_in2]<<(28-(i*4));
    }
    return output;
}

uint64_t left_shift(uint64_t input , uint64_t no_of_round){
    uint64_t output = 0;
    uint64_t amount_of_shift=2;
    uint64_t left_bit=0;
    if(no_of_round==1 || no_of_round==2 || no_of_round==9 || no_of_round==16)
    {
        amount_of_shift=1;
        left_bit |=  (input & 0x8000000)>>27;
        input&= ~0x8000000;
        input<<=amount_of_shift;
        output=input|left_bit;
    }
    else{
        left_bit |=  (input & 0xc000000)>>26;
        input&= ~0xc000000;
        input<<=amount_of_shift;
        output=input|left_bit;
    }
    return output;
}

uint64_t round_permutation(uint64_t input){
    int P[] = {
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
    };
    uint64_t output = 0;
    for (int i = 0; i < 32; ++i) {
        output |= ((input >> (32 - P[i])) & 1) << (31 - i);
    }
    return output;
}

uint64_t inverse_initial_Permutation(uint64_t input) {
    int ip[] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25
    };
    uint64_t output = 0;
    for (int i = 0; i < 64; ++i) {
        output |= ((input >> (64 - ip[i])) & 1) << (63 - i);
    }
    return output;
}

uint64_t swap_32(uint64_t L16 ,uint64_t R16){
    uint64_t output = 0;
    output = (L16) | (R16<<32);
    return output;
}

uint64_t Xor(uint64_t input1 ,uint64_t input2){
    return input1 ^ input2;
}

uint64_t F_function(uint64_t Ri_1 , uint64_t Ki){
    uint64_t temp1 = expansion_permutation(Ri_1);
    uint64_t temp2 = Xor(temp1,Ki);
    uint64_t temp3 = substitution_choice(temp2);
    uint64_t output = round_permutation(temp3);
    return output;
}

uint64_t* round(uint64_t Li_1,uint64_t Ri_1,uint64_t Ci_1,uint64_t Di_1,uint64_t round_no){
    uint64_t Li = Ri_1;
    uint64_t Ci = left_shift(Ci_1,round_no);
    uint64_t Di = left_shift(Di_1,round_no);
    uint64_t Ki = pc_2(Ci,Di);
    uint64_t Ri = Xor(Li_1,F_function(Ri_1,Ki));
    uint64_t *round_result = (uint64_t*)malloc(4 * sizeof(uint64_t));
    round_result[0] = Li;
    round_result[1] = Ri;
    round_result[2] = Ci;
    round_result[3] = Di;
    return round_result;
}

uint64_t DES_encryption(uint64_t plain_text,uint64_t key) {
    uint64_t temp1 = initial_Permutation(plain_text);
    uint64_t Li_1 = temp1 >> 32;
    uint64_t Ri_1 = temp1 & 0xffffffff;
    uint64_t sub_key = PC_1(key);
    uint64_t Ci_1 = sub_key >> 28;
    uint64_t Di_1 = sub_key & 0xfffffff;

    for(int i=1; i<=16 ;i++) {
        uint64_t *round_output = round(Li_1,Ri_1,Ci_1,Di_1,i);
        Li_1 = round_output[0];
        Ri_1 = round_output[1];
        Ci_1 = round_output[2];
        Di_1 = round_output[3];
        free(round_output);
    }
    uint64_t cipher_text = inverse_initial_Permutation(swap_32(Li_1,Ri_1));
    return cipher_text;
}

uint64_t* get_decryption_keys(uint64_t key) {
    uint64_t sub_key = PC_1(key);
    uint64_t Ci_1 = sub_key >> 28;
    uint64_t Di_1 = sub_key & 0xfffffff;
    uint64_t *keys = (uint64_t*)malloc(16 * sizeof(uint64_t));
    for(int i=1;i<=16;i++) {
        Ci_1 = left_shift(Ci_1,i);
        Di_1 = left_shift(Di_1,i);
        keys[16-i] = pc_2(Ci_1,Di_1);
    }
    return keys;
}

uint64_t* round_decryption(uint64_t Li_1,uint64_t Ri_1,uint64_t Ki) {
    uint64_t Ri = Xor(Li_1,F_function(Ri_1,Ki));
    uint64_t Li = Ri_1;
    uint64_t *round_result = (uint64_t*)malloc(2 * sizeof(uint64_t));
    round_result[0] = Li;
    round_result[1] = Ri;
    return round_result;
}

uint64_t DES_Decryption(uint64_t cipherText,uint64_t key) {
    uint64_t temp1 = initial_Permutation(cipherText);
    uint64_t Li_1 = temp1 >> 32;
    uint64_t Ri_1 = temp1 & 0xffffffff;
    uint64_t *keys = get_decryption_keys(key);
    for(int i=1; i<=16 ;i++) {
        uint64_t *round_output = round_decryption(Li_1,Ri_1,keys[i-1]);
        Li_1 = round_output[0];
        Ri_1 = round_output[1];
        free(round_output);
    }
    free(keys);
    uint64_t planeText = inverse_initial_Permutation(swap_32(Li_1,Ri_1));
    return planeText;
}

void converter_1024_to_64_bit_blocks(unsigned char input_data[1024], uint64_t output_data[128])
{
    for(uint64_t i = 0; i < 128; i++)
    {
        for(uint64_t j = 0; j < 8; j++)
        {
            output_data[i] |= ((uint64_t)input_data[(i * 8) + j] << (j * 8));
        }
    }
}
void converter_64_bit_blocks_to_1024(uint64_t input_data[128] ,unsigned char output_data[1024])
{
    for(int i = 0; i < 128; i++)
    {
        for(int j = 0; j < 8; j++)
        {
                output_data[(i * 8)+j]=(input_data[i]>>(j * 8))&(0xff);
        }
    }
}
uint64_t read_key_from_inputFile(unsigned char textKey[8])
{
    uint64_t key=0;
     for(uint64_t j = 0; j < 8; j++)
     {
         key |= ((uint64_t)textKey[j] << (j * 8));
     }
     return key;
}

unsigned char* load_file(const char *fn, int *len) {
    //printf("I entered load_file_function \n");
    struct stat info={0};
    int ret = stat(fn, &info);
    //printf("ret = %d \n",ret);
    if(ret){
        //printf("I entered ret \n");
         return 0;
    }
    FILE *fsrc = fopen(fn, "rb");
    if(!fsrc){
            //printf("I entered fsrc \n");
            return 0;
    }
    //printf("info.st_size %d \n",info.st_size);
    unsigned char * data = (unsigned char *)malloc(info.st_size);
    if(!data) {
        //printf("I entered");
        exit(1);
        return 0;
    }
    //printf("data : %s \n",data);
    size_t nread = fread(data, 1, info.st_size, fsrc);
    //printf("data : %s \n",data);
    //printf("before fclose \n");
    fclose(fsrc);
    //printf("after fclose \n");
    *len=(int)nread;
    //printf("data retrieved : %s",data);
    return data;
}

int save_file(const char *fn, unsigned char *data, int len) {
    FILE *fdst=fopen(fn, "wb");
    if(!fdst) return 0;
    fwrite(data, 1, len, fdst);
    fclose(fdst);
    return 1;
}

int main(int argc, char **argv) {
    char x = argv[1][0];
    unsigned char *keyFileName = argv[2];
    unsigned char *plainTextFileName = argv[3];
    unsigned char *cipherFileName = argv[4];
    //printf("%s %s \n",key_data,plainText_data);
    if(x == 'e'){
        int key_size = 0;
        unsigned char *key_text = load_file(keyFileName,&key_size);
        int plainText_size = 0;
        unsigned char *plainText = load_file(plainTextFileName,&plainText_size);
        printf("key entered : %s , key_size : %i\nplaintext entered : %s , plaintext_size : %i",key_text,key_size,plainText,plainText_size);
        //save_file(cipherFileName,"thisIsTheCipher2",plainText_size);
        uint64_t cipher_blocks[128]={0};
        uint64_t plainText_blocks[128]={0};
        converter_1024_to_64_bit_blocks(plainText,plainText_blocks);
        uint64_t key_binary = read_key_from_inputFile(key_text);
        for(int i=0;i<128;i++){
            cipher_blocks[i] = DES_encryption(plainText_blocks[i],key_binary);
        }
        unsigned char cipher_text[1024]={0};
        converter_64_bit_blocks_to_1024(cipher_blocks,cipher_text);
        save_file(cipherFileName,cipher_text,plainText_size);
    }
    //Decryption
    else{

    }
    /*
    //uint64_t cipherText = DES_encryption(0xFEDCBA987654321,0x133457799BBCDFF1);
    uint64_t cipherText = DES_encryption(0x0123456789ABCDEF,0x133457799BBCDFF1);
    printf("%llu\n", cipherText);
    printf("%llu\n", DES_Decryption(cipherText,0x133457799BBCDFF1));
    char x[100];
    scanf("%s", x);
    uint64_t res=0;
    int sizee = (strlen(x)%8==0)? (strlen(x)/8):((strlen(x)/8)+1);
    uint64_t *blocks_of_plaintext = (uint64_t*)malloc(sizee * sizeof(uint64_t));
    for(int i=0;i<strlen(x);i++) {
        res |= ((uint64_t)x[i])<<((7-i)*8);
        if(i!=0 && (i+1)%8==0) {
            blocks_of_plaintext[(i+1)/8] = res;
            res=0;
        }
    }
    for(int i=0;i<sizee;i++) {
        printf("%llu\n", DES_encryption(blocks_of_plaintext[i],0x133457799BBCDFF1));
        printf("%llu\n", DES_Decryption(DES_encryption(blocks_of_plaintext[i],0x133457799BBCDFF1),0x133457799BBCDFF1));
    }
    free(blocks_of_plaintext);
    return 0;
    */
}

