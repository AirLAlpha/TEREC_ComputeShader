/**********************************************
 *
 *  Calc_CS.hlsl
 *  �v�Z���s���R���s���[�g�V�F�[�_�[
 *
 *  ����ҁF���ە��m
 *  ������F2024/01/15
 *
 **********************************************/

//  �N�C�Y����̍\����
struct Question
{
    int a;
    int b;
};

//  ���͗p�o�b�t�@�iShaderResourcesView�j
StructuredBuffer<Question> inBuff : register(t0);
//  �o�͗p�o�b�t�@�iUnorderedAccessView�j
RWStructuredBuffer<int> outBuff : register(u0);


//  �X���b�h��
#define THREAD_X    256
#define THREAD_Y    1
#define THREAD_Z    1


[numthreads(THREAD_X, THREAD_Y, THREAD_Z)]
void main( uint3 DTid : SV_DispatchThreadID )
{
    uint index = DTid.x;
    
    //  �v�Z���s��
    outBuff[index] = inBuff[index].a + inBuff[index].b;
}