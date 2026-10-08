.code

Vec3_Add PROC
	movss   xmm0, dword ptr [rcx]        
    addss   xmm0, dword ptr [rdx]        
    movss   xmm1, dword ptr [rcx+4]      
    addss   xmm1, dword ptr [rdx+4]     
    movss   xmm2, dword ptr [rcx+8]      
    addss   xmm2, dword ptr [rdx+8]     

    movss   dword ptr [r8],   xmm0      
    movss   dword ptr [r8+4], xmm1      
    movss   dword ptr [r8+8], xmm2  
	ret
Vec3_Add ENDP

END