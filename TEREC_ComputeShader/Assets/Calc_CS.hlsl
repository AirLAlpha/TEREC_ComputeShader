/**********************************************
 *
 *  Calc_CS.hlsl
 *  計算を行うコンピュートシェーダー
 *
 *  製作者：牛丸文仁
 *  制作日：2024/01/15
 *
 **********************************************/

//  クイズ一つ分の構造体
struct Question
{
    int a;
    int b;
};

//  入力用バッファ（ShaderResourcesView）
StructuredBuffer<Question> inBuff : register(t0);
//  出力用バッファ（UnorderedAccessView）
RWStructuredBuffer<int> outBuff : register(u0);


//  スレッド数
#define THREAD_X    256
#define THREAD_Y    1
#define THREAD_Z    1


[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint index = DTid.x;
    
    //  計算を行う
    outBuff[index] = inBuff[index].a + inBuff[index].b;
}