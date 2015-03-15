// このファイルはpythonで適当に作ったファイルを適当に書き換えたものです

#define CINTERFACE

#include "d3dx9.h"

#include <windows.h>
#include <string>
#include <sstream>
#include <tchar.h>
#include <fstream>
#include <algorithm>
#include <shlwapi.h>
#include <vector>
#include <map>

#include <Python.h>

template <class T> std::string to_string(T value)
{
	std::stringstream converter;
	std::string  str;
	converter << value;
	converter >> str;
	return str;
}

HRESULT (WINAPI *original_SetFloatArray)(
	ID3DXEffect* pEffect,
	D3DXHANDLE hParameter,
	CONST FLOAT* pf,
	UINT Count)(NULL);

D3DXHANDLE (WINAPI *original_GetParameter)(
	ID3DXEffect* pEffect,
	D3DXHANDLE hParent,
	UINT index)(NULL);

HRESULT (WINAPI *original_SetTexture)(
	ID3DXEffect* pEffect,
	D3DXHANDLE hParameter,
	LPDIRECT3DBASETEXTURE9 pTexture
	)(NULL);

///-----------------------------------------------------D3DX------------------------------------------------

HRESULT(WINAPI *original_D3DXComputeNormals)(
	LPD3DXBASEMESH pMesh,
	CONST DWORD *pAdjacency)(NULL);

HRESULT(WINAPI *original_D3DXCreateEffectFromResourceA)(
	LPDIRECT3DDEVICE9		    pDevice,
	HMODULE						 hSrcModule,
	LPCSTR						  pSrcResource,
	CONST D3DXMACRO*				pDefines,
	LPD3DXINCLUDE				pInclude,
	DWORD						Flags,
	LPD3DXEFFECTPOOL				pPool,
	LPD3DXEFFECT*				ppEffect,
	LPD3DXBUFFER*				ppCompilationErrors)(NULL);

HRESULT(WINAPI *original_D3DXCreateTexture)(
	LPDIRECT3DDEVICE9		 pDevice,
	UINT				   Width,
	UINT				   Height,
	UINT				   MipLevels,
	DWORD				  Usage,
	D3DFORMAT				 Format,
	D3DPOOL				Pool,
	LPDIRECT3DTEXTURE9*       ppTexture)(NULL);

HRESULT(WINAPI *original_D3DXCreateTextureFromFileExA)(
	LPDIRECT3DDEVICE9		 pDevice,
	LPCSTR				 pSrcFile,
	UINT				   Width,
	UINT				   Height,
	UINT				   MipLevels,
	DWORD				  Usage,
	D3DFORMAT				 Format,
	D3DPOOL				Pool,
	DWORD				  Filter,
	DWORD				  MipFilter,
	D3DCOLOR				  ColorKey,
	D3DXIMAGE_INFO*		pSrcInfo,
	PALETTEENTRY*		  pPalette,
	LPDIRECT3DTEXTURE9*       ppTexture)(NULL);

HRESULT(WINAPI *original_D3DXCreateTextureFromFileExW)(
	LPDIRECT3DDEVICE9		 pDevice,
	LPCWSTR				pSrcFile,
	UINT				   Width,
	UINT				   Height,
	UINT				   MipLevels,
	DWORD				  Usage,
	D3DFORMAT				 Format,
	D3DPOOL				Pool,
	DWORD				  Filter,
	DWORD				  MipFilter,
	D3DCOLOR				  ColorKey,
	D3DXIMAGE_INFO*		pSrcInfo,
	PALETTEENTRY*		  pPalette,
	LPDIRECT3DTEXTURE9*       ppTexture)(NULL);

HRESULT(WINAPI *original_D3DXCreateTextureFromFileInMemoryEx)(
	LPDIRECT3DDEVICE9		 pDevice,
	LPCVOID				pSrcData,
	UINT				   SrcDataSize,
	UINT				   Width,
	UINT				   Height,
	UINT				   MipLevels,
	DWORD				  Usage,
	D3DFORMAT				 Format,
	D3DPOOL				Pool,
	DWORD				  Filter,
	DWORD				  MipFilter,
	D3DCOLOR				  ColorKey,
	D3DXIMAGE_INFO*		pSrcInfo,
	PALETTEENTRY*		  pPalette,
	LPDIRECT3DTEXTURE9*       ppTexture)(NULL);

HRESULT(WINAPI *original_D3DXLoadMeshFromXInMemory)(
	LPCVOID Memory,
	DWORD SizeOfMemory,
	DWORD Options,
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPD3DXBUFFER *ppAdjacency,
	LPD3DXBUFFER *ppMaterials,
	LPD3DXBUFFER *ppEffectInstances,
	DWORD *pNumMaterials,
	LPD3DXMESH *ppMesh)(NULL);

HRESULT(WINAPI *original_D3DXLoadMeshFromXW)(
	LPCWSTR pFilename,
	DWORD Options,
	LPDIRECT3DDEVICE9 pD3DDevice,
	LPD3DXBUFFER *ppAdjacency,
	LPD3DXBUFFER *ppMaterials,
	LPD3DXBUFFER *ppEffectInstances,
	DWORD *pNumMaterials,
	LPD3DXMESH *ppMesh)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixInverse)(
	D3DXMATRIX *pOut,
	FLOAT *pDeterminant,
	CONST D3DXMATRIX *pM
	)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixLookAtLH)(
	D3DXMATRIX *pOut,
	CONST D3DXVECTOR3 *pEye,
	CONST D3DXVECTOR3 *pAt,
	CONST D3DXVECTOR3 *pUp)(NULL);

D3DXMATRIX * (WINAPI *original_D3DXMatrixMultiply
			  )	(D3DXMATRIX *pOut,
			  CONST D3DXMATRIX *pM1,
			  CONST D3DXMATRIX *pM2
			  )(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixPerspectiveFovLH)(
	D3DXMATRIX *pOut,
	FLOAT fovy,
	FLOAT Aspect,
	FLOAT zn,
	FLOAT zf)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixRotationQuaternion)(
	D3DXMATRIX *pOut,
	CONST D3DXQUATERNION *pQ)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixRotationX)(
	D3DXMATRIX *pOut,
	FLOAT Angle)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixRotationY)(
	D3DXMATRIX *pOut,
	FLOAT Angle)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixRotationZ)(
	D3DXMATRIX *pOut,
	FLOAT Angle)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixScaling)(
	D3DXMATRIX *pOut,
	FLOAT sx,
	FLOAT sy,
	FLOAT sz)(NULL);

D3DXMATRIX* (WINAPI *original_D3DXMatrixTranslation)(
	D3DXMATRIX *pOut,
	FLOAT x,
	FLOAT y,
	FLOAT z)(NULL);

D3DXQUATERNION* (WINAPI *original_D3DXQuaternionInverse)(
	D3DXQUATERNION *pOut,
	CONST D3DXQUATERNION *pQ)(NULL);

D3DXQUATERNION* (WINAPI *original_D3DXQuaternionMultiply)(
	D3DXQUATERNION *pOut,
	CONST D3DXQUATERNION *pQ1,
	CONST D3DXQUATERNION *pQ2)(NULL);

D3DXQUATERNION* (WINAPI *original_D3DXQuaternionNormalize)(
	D3DXQUATERNION *pOut,
	CONST D3DXQUATERNION *pQ)(NULL);

D3DXQUATERNION* (WINAPI *original_D3DXQuaternionRotationAxis)(
	D3DXQUATERNION *pOut,
	CONST D3DXVECTOR3 *pV,
	FLOAT Angle)(NULL);

D3DXQUATERNION* (WINAPI *original_D3DXQuaternionRotationMatrix)(
	D3DXQUATERNION *pOut,
	CONST D3DXMATRIX *pM)(NULL);

void (WINAPI *original_D3DXQuaternionToAxisAngle)(
	CONST D3DXQUATERNION *pQ,
	D3DXVECTOR3 *pAxis,
	FLOAT *pAngle)(NULL);

HRESULT(WINAPI *original_D3DXSaveSurfaceToFileW)(
	LPCWSTR				pDestFile,
	D3DXIMAGE_FILEFORMAT      DestFormat,
	LPDIRECT3DSURFACE9		pSrcSurface,
	CONST PALETTEENTRY*       pSrcPalette,
	CONST RECT*		    pSrcRect)(NULL);

D3DXVECTOR3* (WINAPI *original_D3DXVec3Normalize)(
	D3DXVECTOR3 *pOut,
	CONST D3DXVECTOR3 *pV)(NULL);

D3DXVECTOR4* (WINAPI *original_D3DXVec3Transform)(
	D3DXVECTOR4 *pOut,
	CONST D3DXVECTOR3 *pV,
	CONST D3DXMATRIX *pM)(NULL);

///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///

int effectFlag = 0;
bool showFloatArray = false;

D3DXVECTOR4 fovlh(0.0f, 0.0f, 0.0f, 0.0f);

D3DXVECTOR3 v_eye(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 v_up(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 v_at(0.0f, 0.0f, 0.0f);

std::map<LPDIRECT3DTEXTURE9, std::pair<std::wstring, D3DFORMAT>> dxTextureMap;

void UMSetFlag(int flag)
{
	showFloatArray = (flag > 0) ;
}

void UMSync()
{
	effectFlag = 0;
}

int UMGetEffectType()
{
	return effectFlag;
}

void UMGetCameraFovLH(D3DXVECTOR4 *dst)
{
	dst->x = fovlh.x;
	dst->y = fovlh.y;
	dst->z = fovlh.z;
	dst->w = fovlh.w;
}

void UMGetCameraEye(D3DXVECTOR3 *dst)
{
	dst->x = v_eye.x;
	dst->y = v_eye.y;
	dst->z = v_eye.z;
}

void UMGetCameraAt(D3DXVECTOR3 *dst)
{
	dst->x = v_at.x;
	dst->y = v_at.y;
	dst->z = v_at.z;
}

void UMGetCameraUp(D3DXVECTOR3 *dst)
{
	dst->x = v_up.x;
	dst->y = v_up.y;
	dst->z = v_up.z;
}

BOOL UMCopyTexture(LPCWSTR dstDir, LPDIRECT3DTEXTURE9 tex)
{
	std::map<LPDIRECT3DTEXTURE9, std::pair<std::wstring, D3DFORMAT> >::iterator it = dxTextureMap.find(tex);

	if (it != dxTextureMap.end()) {
		LPCWSTR srcPath = (*it).second.first.c_str();
		if (PathFileExists(srcPath)) {
			WCHAR fileName[MAX_PATH];
			short size = GetFileTitle(srcPath, NULL, NULL);
			GetFileTitle(srcPath, fileName, size);

			std::wstring dst(std::wstring(dstDir) + std::wstring(fileName));

			CopyFile(srcPath, dst.c_str(), false);
		}

	} else {
		return false;
	}
	return true;
}

LPWSTR UMGetTextureName(LPDIRECT3DTEXTURE9 tex)
{
	std::map<LPDIRECT3DTEXTURE9, std::pair<std::wstring, D3DFORMAT> >::iterator it = dxTextureMap.find(tex);

	static WCHAR dst[MAX_PATH];

	if (it != dxTextureMap.end()) {
		LPCWSTR srcPath = (*it).second.first.c_str();
		if (PathFileExists(srcPath)) {
			short size = GetFileTitle(srcPath, NULL, NULL);
			GetFileTitle(srcPath, dst, size);
		}
	}
	return dst;
}

BOOL UMIsAlphaTexture(LPDIRECT3DTEXTURE9 tex)
{
	std::map<LPDIRECT3DTEXTURE9, std::pair<std::wstring, D3DFORMAT> >::iterator it = dxTextureMap.find(tex);

	if (it != dxTextureMap.end()) {
		if ((*it).second.second == D3DFMT_A8R8G8B8) {
			return true;
		}
	}
	return false;

}

HRESULT WINAPI setTexture(
						  ID3DXEffect* pEffect,
						  D3DXHANDLE hParameter,
						  LPDIRECT3DBASETEXTURE9 pTexture
						  )
{
	//::MessageBoxA(NULL, hParameter, "texture", MB_OK);
	return original_SetTexture(pEffect, hParameter, pTexture);
}

HRESULT WINAPI setFloatArray(
							 ID3DXEffect* pEffect,
							 D3DXHANDLE hParameter,
							 CONST FLOAT* pf,
							 UINT Count
							 )
{
	std::string param(hParameter);
	if (param == "EgColor")
		effectFlag |= EgColor;
	if (param == "ToonColor")
		effectFlag |= ToonColor;
	if (param == "SpcColor")
		effectFlag |= SpcColor;
	if (param == "DifColor")
		effectFlag |= DifColor;

	return original_SetFloatArray(pEffect, hParameter, pf, Count);
}

D3DXHANDLE WINAPI getParameter(
							   ID3DXEffect* pEffect,
							   D3DXHANDLE hParent,
							   UINT index
							   )
{
	//::MessageBoxA(NULL, hParent, "param", MB_OK);
	return original_GetParameter(pEffect, hParent, index);
}




extern "C" {


	HRESULT WINAPI D3DXComputeNormals(
		LPD3DXBASEMESH pMesh,
		CONST DWORD *pAdjacency)
	{
		return (*original_D3DXComputeNormals)(pMesh, pAdjacency);
	}

	std::vector<LPD3DXEFFECT*> effects;

	LPD3DXEFFECT* UMGetEffect()
	{
		if (effects.size() > 0) {
			return effects[0];
		} else {
			return NULL;
		}

	}

	int UMGetEffectSize()
	{
		return effects.size();
	}

	HRESULT WINAPI D3DXCreateEffectFromResourceA(
		LPDIRECT3DDEVICE9		    pDevice,
		HMODULE						 hSrcModule,
		LPCSTR						  pSrcResource,
		CONST D3DXMACRO*				pDefines,
		LPD3DXINCLUDE				pInclude,
		DWORD						Flags,
		LPD3DXEFFECTPOOL				pPool,
		LPD3DXEFFECT*				ppEffect,
		LPD3DXBUFFER*				ppCompilationErrors)
	{
		HRESULT res = (*original_D3DXCreateEffectFromResourceA)(pDevice, hSrcModule, pSrcResource, pDefines, pInclude, Flags, pPool, ppEffect, ppCompilationErrors);

		effects.push_back(ppEffect);


		original_SetFloatArray = (*ppEffect)->lpVtbl->SetFloatArray;
		//original_SetTexture = (*ppEffect)->lpVtbl->SetTexture;
		//original_GetParameter = 	(*ppEffect)->lpVtbl->GetParameter;

		// 書き込み属性付与
		DWORD old_protect;
		VirtualProtect(reinterpret_cast<void *>((*ppEffect)->lpVtbl), sizeof((*ppEffect)->lpVtbl), PAGE_EXECUTE_WRITECOPY, &old_protect);

		(*ppEffect)->lpVtbl->SetFloatArray = setFloatArray;
		//(*ppEffect)->lpVtbl->SetTexture = setTexture;
		//(*ppEffect)->lpVtbl->GetParameter = getParameter;

		// 書き込み属性元に戻す
		VirtualProtect(reinterpret_cast<void *>((*ppEffect)->lpVtbl), sizeof((*ppEffect)->lpVtbl), old_protect, &old_protect);

		return res;
	}

	HRESULT WINAPI D3DXCreateTexture(
		LPDIRECT3DDEVICE9		 pDevice,
		UINT				   Width,
		UINT				   Height,
		UINT				   MipLevels,
		DWORD				  Usage,
		D3DFORMAT				 Format,
		D3DPOOL				Pool,
		LPDIRECT3DTEXTURE9*       ppTexture)
	{
		//::MessageBoxA(NULL, "D3DXCreateTexture", "d3dx", MB_OK);
		return (*original_D3DXCreateTexture)(pDevice, Width, Height, MipLevels, Usage, Format, Pool, ppTexture);
	}

	HRESULT WINAPI D3DXCreateTextureFromFileExA(
		LPDIRECT3DDEVICE9		 pDevice,
		LPCSTR				 pSrcFile,
		UINT				   Width,
		UINT				   Height,
		UINT				   MipLevels,
		DWORD				  Usage,
		D3DFORMAT				 Format,
		D3DPOOL				Pool,
		DWORD				  Filter,
		DWORD				  MipFilter,
		D3DCOLOR				  ColorKey,
		D3DXIMAGE_INFO*		pSrcInfo,
		PALETTEENTRY*		  pPalette,
		LPDIRECT3DTEXTURE9*       ppTexture)
	{
		//::MessageBoxA(NULL, "D3DXCreateTextureFromFileExA", "d3dx", MB_OK);
		return (*original_D3DXCreateTextureFromFileExA)(pDevice, pSrcFile, Width, Height, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppTexture);
	}

	HRESULT WINAPI D3DXCreateTextureFromFileExW(
		LPDIRECT3DDEVICE9		 pDevice,
		LPCWSTR				pSrcFile,
		UINT				   Width,
		UINT				   Height,
		UINT				   MipLevels,
		DWORD				  Usage,
		D3DFORMAT				 Format,
		D3DPOOL				Pool,
		DWORD				  Filter,
		DWORD				  MipFilter,
		D3DCOLOR				  ColorKey,
		D3DXIMAGE_INFO*		pSrcInfo,
		PALETTEENTRY*		  pPalette,
		LPDIRECT3DTEXTURE9*       ppTexture)
	{
		HRESULT res = (*original_D3DXCreateTextureFromFileExW)(pDevice, pSrcFile, Width, Height, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppTexture);

		//{
		//	D3DXIMAGE_INFO info;
		//	LPDIRECT3DTEXTURE9 tmpTex;

		//	HRESULT res2 = (*original_D3DXCreateTextureFromFileExW)(pDevice, pSrcFile, Width, Height, MipLevels, Usage, D3DFMT_UNKNOWN, Pool, Filter, MipFilter, ColorKey, &info, pPalette, &tmpTex);
		//	if (SUCCEEDED(res2))
		//	{
		//		::MessageBoxA(NULL, to_string(info.).c_str(), "info", MB_OK);
		//		tmpTex->lpVtbl->Release(tmpTex);
		//	}
		//}

		if (SUCCEEDED(res)) {
			if (dxTextureMap.find(*ppTexture) != dxTextureMap.end()) {
				dxTextureMap.erase(*ppTexture);

			}
			dxTextureMap[*ppTexture] = std::pair<std::wstring, D3DFORMAT>(pSrcFile, pSrcInfo->Format);

		}
		return res;
	}

	HRESULT WINAPI D3DXCreateTextureFromFileInMemoryEx(
		LPDIRECT3DDEVICE9		 pDevice,
		LPCVOID				pSrcData,
		UINT				   SrcDataSize,
		UINT				   Width,
		UINT				   Height,
		UINT				   MipLevels,
		DWORD				  Usage,
		D3DFORMAT				 Format,
		D3DPOOL				Pool,
		DWORD				  Filter,
		DWORD				  MipFilter,
		D3DCOLOR				  ColorKey,
		D3DXIMAGE_INFO*		pSrcInfo,
		PALETTEENTRY*		  pPalette,
		LPDIRECT3DTEXTURE9*       ppTexture)
	{
		//::MessageBoxA(NULL, "D3DXCreateTextureFromFileInMemoryEx", "d3dx", MB_OK);
		return (*original_D3DXCreateTextureFromFileInMemoryEx)(pDevice, pSrcData, SrcDataSize, Width, Height, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppTexture);
	}

	HRESULT WINAPI D3DXLoadMeshFromXInMemory(
		LPCVOID Memory,
		DWORD SizeOfMemory,
		DWORD Options,
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPD3DXBUFFER *ppAdjacency,
		LPD3DXBUFFER *ppMaterials,
		LPD3DXBUFFER *ppEffectInstances,
		DWORD *pNumMaterials,
		LPD3DXMESH *ppMesh)
	{
		return (*original_D3DXLoadMeshFromXInMemory)(Memory, SizeOfMemory, Options, pD3DDevice, ppAdjacency, ppMaterials, ppEffectInstances, pNumMaterials, ppMesh);
	}

	HRESULT WINAPI D3DXLoadMeshFromXW(
		LPCWSTR pFilename,
		DWORD Options,
		LPDIRECT3DDEVICE9 pD3DDevice,
		LPD3DXBUFFER *ppAdjacency,
		LPD3DXBUFFER *ppMaterials,
		LPD3DXBUFFER *ppEffectInstances,
		DWORD *pNumMaterials,
		LPD3DXMESH *ppMesh)
	{
		return (*original_D3DXLoadMeshFromXW)(pFilename, Options, pD3DDevice, ppAdjacency, ppMaterials, ppEffectInstances, pNumMaterials, ppMesh);
	}

	D3DXMATRIX* WINAPI D3DXMatrixInverse(
		D3DXMATRIX *pOut,
		FLOAT *pDeterminant,
		CONST D3DXMATRIX *pM)
	{
		return (*original_D3DXMatrixInverse)(pOut, pDeterminant, pM);
	}


	D3DXMATRIX* WINAPI D3DXMatrixLookAtLH(
		D3DXMATRIX *pOut,
		CONST D3DXVECTOR3 *pEye,
		CONST D3DXVECTOR3 *pAt,
		CONST D3DXVECTOR3 *pUp)
	{
		if (pUp->y == 1) {
			v_eye.x = pEye->x;
			v_eye.y = pEye->y;
			v_eye.z = pEye->z;

			v_up.x = pUp->x;
			v_up.y = pUp->y;
			v_up.z = pUp->z;

			v_at.x = pAt->x;
			v_at.y = pAt->y;
			v_at.z = pAt->z;
		}
		//
		//::MessageBoxA(NULL,
		//	std::string(
		//	"up" + to_string(pUp->x)+" "+to_string(pUp->y)+" "+to_string(pUp->z)+"\n"
		//	+"at" + to_string(pAt->x)+" "+to_string(pAt->y)+" "+to_string(pAt->z)+"\n"
		//	+"eye" + to_string(pEye->x)+" "+to_string(pEye->y)+" "+to_string(pEye->z)+"\n").c_str(), "lookat", MB_OK);
		return (*original_D3DXMatrixLookAtLH)(pOut, pEye, pAt, pUp);
	}

	D3DXMATRIX * WINAPI D3DXMatrixMultiply(D3DXMATRIX *pOut,
		CONST D3DXMATRIX *pM1,
		CONST D3DXMATRIX *pM2)
	{
		return (*original_D3DXMatrixMultiply)(pOut, pM1, pM2);
	}

	D3DXMATRIX* WINAPI D3DXMatrixPerspectiveFovLH(
		D3DXMATRIX *pOut,
		FLOAT fovy,
		FLOAT Aspect,
		FLOAT zn,
		FLOAT zf)
	{
		fovlh.x = fovy;
		fovlh.y = Aspect;
		fovlh.z = zn;
		fovlh.w = zf;
		return (*original_D3DXMatrixPerspectiveFovLH)(pOut, fovy, Aspect, zn, zf);
	}

	D3DXMATRIX* WINAPI D3DXMatrixRotationQuaternion(
		D3DXMATRIX *pOut,
		CONST D3DXQUATERNION *pQ)
	{
		return (*original_D3DXMatrixRotationQuaternion)(pOut, pQ);
	}

	D3DXMATRIX* WINAPI D3DXMatrixRotationX(
		D3DXMATRIX *pOut,
		FLOAT Angle)
	{
		return (*original_D3DXMatrixRotationX)(pOut, Angle);
	}

	D3DXMATRIX* WINAPI D3DXMatrixRotationY(
		D3DXMATRIX *pOut,
		FLOAT Angle)
	{
		return (*original_D3DXMatrixRotationY)(pOut, Angle);
	}

	D3DXMATRIX* WINAPI D3DXMatrixRotationZ(
		D3DXMATRIX *pOut,
		FLOAT Angle)
	{
		return (*original_D3DXMatrixRotationZ)(pOut, Angle);
	}

	D3DXMATRIX* WINAPI D3DXMatrixScaling(
		D3DXMATRIX *pOut,
		FLOAT sx,
		FLOAT sy,
		FLOAT sz)
	{
		return (*original_D3DXMatrixScaling)(pOut, sx, sy, sz);
	}

	D3DXMATRIX* WINAPI D3DXMatrixTranslation(
		D3DXMATRIX *pOut,
		FLOAT x,
		FLOAT y,
		FLOAT z)
	{
		return (*original_D3DXMatrixTranslation)(pOut, x, y, z);
	}

	D3DXQUATERNION* WINAPI D3DXQuaternionInverse(
		D3DXQUATERNION *pOut,
		CONST D3DXQUATERNION *pQ)
	{
		return (*original_D3DXQuaternionInverse)(pOut, pQ);
	}

	D3DXQUATERNION* WINAPI D3DXQuaternionMultiply(
		D3DXQUATERNION *pOut,
		CONST D3DXQUATERNION *pQ1,
		CONST D3DXQUATERNION *pQ2)
	{
		return (*original_D3DXQuaternionMultiply)(pOut, pQ1, pQ2);
	}

	D3DXQUATERNION* WINAPI D3DXQuaternionNormalize(
		D3DXQUATERNION *pOut,
		CONST D3DXQUATERNION *pQ)
	{
		return (*original_D3DXQuaternionNormalize)(pOut, pQ);
	}

	D3DXQUATERNION* WINAPI D3DXQuaternionRotationAxis(
		D3DXQUATERNION *pOut,
		CONST D3DXVECTOR3 *pV,
		FLOAT Angle)
	{
		return (*original_D3DXQuaternionRotationAxis)(pOut, pV, Angle);
	}

	D3DXQUATERNION* WINAPI D3DXQuaternionRotationMatrix(
		D3DXQUATERNION *pOut,
		CONST D3DXMATRIX *pM)
	{
		return (*original_D3DXQuaternionRotationMatrix)(pOut, pM);
	}

	void WINAPI D3DXQuaternionToAxisAngle(
		CONST D3DXQUATERNION *pQ,
		D3DXVECTOR3 *pAxis,
		FLOAT *pAngle)
	{
		return (*original_D3DXQuaternionToAxisAngle)(pQ, pAxis, pAngle);
	}

	HRESULT WINAPI D3DXSaveSurfaceToFileW(
		LPCWSTR				pDestFile,
		D3DXIMAGE_FILEFORMAT      DestFormat,
		LPDIRECT3DSURFACE9		pSrcSurface,
		CONST PALETTEENTRY*       pSrcPalette,
		CONST RECT*		    pSrcRect)
	{
		return (*original_D3DXSaveSurfaceToFileW)(pDestFile, DestFormat, pSrcSurface, pSrcPalette, pSrcRect);
	}

	D3DXVECTOR3* WINAPI D3DXVec3Normalize(
		D3DXVECTOR3 *pOut,
		CONST D3DXVECTOR3 *pV)
	{
		return (*original_D3DXVec3Normalize)(pOut, pV);
	}

	D3DXVECTOR4* WINAPI D3DXVec3Transform(
		D3DXVECTOR4 *pOut,
		CONST D3DXVECTOR3 *pV,
		CONST D3DXMATRIX *pM)
	{
		return (*original_D3DXVec3Transform)(pOut, pV, pM);
	}

} // extern "C"

BOOL init()
{

	TCHAR app_full_path[1024];	// アプリフルパス

	GetModuleFileName(NULL, app_full_path, sizeof(app_full_path) / sizeof(TCHAR));

	//std::wstring pythonScript(app_full_path);
	//pythonScript = pythonScript.substr(0, pythonScript.find_last_of(_T("MikuMikuDance.exe")) -16);
	//pythonScript.append(_T("mmdbridge.py"));

	//std::ifstream ifs(pythonScript.c_str());
	//if (!ifs) return false;
	//char buf[2048];
	//while (ifs.getline( buf, sizeof(buf))) {
	//	mmdbridge_python_script.append(buf);
	//	mmdbridge_python_script.append("\r\n");
	//}

	//::MessageBoxA(NULL, "d3dx9_32.dll読み込みます", "hoge",MB_OK);
	TCHAR system_path_buffer[1024]; // システムパス保存用
	GetSystemDirectory(system_path_buffer, MAX_PATH );
	std::wstring d3d9x_path(system_path_buffer);
	d3d9x_path.append(_T("\\D3DX9_32.DLL"));
	HMODULE d3d9x_module(LoadLibrary(d3d9x_path.c_str())); // オリジナルのD3D9X_32.DLLのモジュール

	if (!d3d9x_module) {
		::MessageBoxA(NULL, "d3dx9_32.dll読み込み失敗", "hoge",MB_OK);
		return FALSE;
	}

	//::MessageBoxA(NULL, "d3dx9_32.dll読み込みました", "hoge",MB_OK);
	//// オリジナルの関数ポインタを取得
	original_D3DXComputeNormals = reinterpret_cast<HRESULT  (WINAPI*)(        LPD3DXBASEMESH pMesh,         CONST DWORD *pAdjacency)>(GetProcAddress(d3d9x_module, "D3DXComputeNormals"));
	original_D3DXCreateEffectFromResourceA = reinterpret_cast<HRESULT  (WINAPI*)(  LPDIRECT3DDEVICE9      pDevice,   HMODULE       hSrcModule,   LPCSTR        pSrcResource,   CONST D3DXMACRO*    pDefines,   LPD3DXINCLUDE    pInclude,   DWORD      Flags,   LPD3DXEFFECTPOOL    pPool,   LPD3DXEFFECT*    ppEffect,   LPD3DXBUFFER*    ppCompilationErrors)>(GetProcAddress(d3d9x_module, "D3DXCreateEffectFromResourceA"));
	original_D3DXCreateTexture = reinterpret_cast<HRESULT  (WINAPI*)(  LPDIRECT3DDEVICE9   pDevice,   UINT       Width,   UINT       Height,   UINT       MipLevels,   DWORD      Usage,   D3DFORMAT     Format,   D3DPOOL    Pool,   LPDIRECT3DTEXTURE9*       ppTexture)>(GetProcAddress(d3d9x_module, "D3DXCreateTexture"));
	original_D3DXCreateTextureFromFileExA = reinterpret_cast<HRESULT  (WINAPI*)(  LPDIRECT3DDEVICE9   pDevice,   LPCSTR     pSrcFile,   UINT       Width,   UINT       Height,   UINT       MipLevels,   DWORD      Usage,   D3DFORMAT     Format,   D3DPOOL    Pool,   DWORD      Filter,   DWORD      MipFilter,   D3DCOLOR      ColorKey,   D3DXIMAGE_INFO*  pSrcInfo,   PALETTEENTRY*    pPalette,   LPDIRECT3DTEXTURE9*       ppTexture)>(GetProcAddress(d3d9x_module, "D3DXCreateTextureFromFileExA"));
	original_D3DXCreateTextureFromFileExW = reinterpret_cast<HRESULT  (WINAPI*)(  LPDIRECT3DDEVICE9   pDevice,   LPCWSTR    pSrcFile,   UINT       Width,   UINT       Height,   UINT       MipLevels,   DWORD      Usage,   D3DFORMAT     Format,   D3DPOOL    Pool,   DWORD      Filter,   DWORD      MipFilter,   D3DCOLOR      ColorKey,   D3DXIMAGE_INFO*  pSrcInfo,   PALETTEENTRY*    pPalette,   LPDIRECT3DTEXTURE9*       ppTexture)>(GetProcAddress(d3d9x_module, "D3DXCreateTextureFromFileExW"));
	original_D3DXCreateTextureFromFileInMemoryEx = reinterpret_cast<HRESULT  (WINAPI*)(  LPDIRECT3DDEVICE9   pDevice,   LPCVOID    pSrcData,   UINT       SrcDataSize,   UINT       Width,   UINT       Height,   UINT       MipLevels,   DWORD      Usage,   D3DFORMAT     Format,   D3DPOOL    Pool,   DWORD      Filter,   DWORD      MipFilter,   D3DCOLOR      ColorKey,   D3DXIMAGE_INFO*  pSrcInfo,   PALETTEENTRY*    pPalette,   LPDIRECT3DTEXTURE9*       ppTexture)>(GetProcAddress(d3d9x_module, "D3DXCreateTextureFromFileInMemoryEx"));
	original_D3DXLoadMeshFromXInMemory = reinterpret_cast<HRESULT  (WINAPI*)(  LPCVOID Memory,   DWORD SizeOfMemory,   DWORD Options,   LPDIRECT3DDEVICE9 pD3DDevice,   LPD3DXBUFFER *ppAdjacency,   LPD3DXBUFFER *ppMaterials,   LPD3DXBUFFER *ppEffectInstances,   DWORD *pNumMaterials,   LPD3DXMESH *ppMesh)>(GetProcAddress(d3d9x_module, "D3DXLoadMeshFromXInMemory"));
	original_D3DXLoadMeshFromXW = reinterpret_cast<HRESULT  (WINAPI*)(  LPCWSTR pFilename,   DWORD Options,   LPDIRECT3DDEVICE9 pD3DDevice,   LPD3DXBUFFER *ppAdjacency,   LPD3DXBUFFER *ppMaterials,   LPD3DXBUFFER *ppEffectInstances,   DWORD *pNumMaterials,   LPD3DXMESH *ppMesh)>(GetProcAddress(d3d9x_module, "D3DXLoadMeshFromXW"));
	original_D3DXMatrixInverse = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT *pDeterminant,   CONST D3DXMATRIX *pM )>(GetProcAddress(d3d9x_module, "D3DXMatrixInverse"));
	original_D3DXMatrixLookAtLH = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   CONST D3DXVECTOR3 *pEye,   CONST D3DXVECTOR3 *pAt,   CONST D3DXVECTOR3 *pUp )>(GetProcAddress(d3d9x_module, "D3DXMatrixLookAtLH"));
	original_D3DXMatrixMultiply = reinterpret_cast<D3DXMATRIX *  (WINAPI*)(  D3DXMATRIX *pOut, CONST D3DXMATRIX *pM1,   CONST D3DXMATRIX *pM2)>(GetProcAddress(d3d9x_module, "D3DXMatrixMultiply"));
	original_D3DXMatrixPerspectiveFovLH = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT fovy,   FLOAT Aspect,   FLOAT zn,   FLOAT zf )>(GetProcAddress(d3d9x_module, "D3DXMatrixPerspectiveFovLH"));
	original_D3DXMatrixRotationQuaternion = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   CONST D3DXQUATERNION *pQ)>(GetProcAddress(d3d9x_module, "D3DXMatrixRotationQuaternion"));
	original_D3DXMatrixRotationX = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT Angle )>(GetProcAddress(d3d9x_module, "D3DXMatrixRotationX"));
	original_D3DXMatrixRotationY = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT Angle )>(GetProcAddress(d3d9x_module, "D3DXMatrixRotationY"));
	original_D3DXMatrixRotationZ = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT Angle )>(GetProcAddress(d3d9x_module, "D3DXMatrixRotationZ"));
	original_D3DXMatrixScaling = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT sx,   FLOAT sy,   FLOAT sz )>(GetProcAddress(d3d9x_module, "D3DXMatrixScaling"));
	original_D3DXMatrixTranslation = reinterpret_cast<D3DXMATRIX*  (WINAPI*)(  D3DXMATRIX *pOut,   FLOAT x,   FLOAT y,   FLOAT z )>(GetProcAddress(d3d9x_module, "D3DXMatrixTranslation"));
	original_D3DXQuaternionInverse = reinterpret_cast<D3DXQUATERNION*  (WINAPI*)(  D3DXQUATERNION *pOut,   CONST D3DXQUATERNION *pQ )>(GetProcAddress(d3d9x_module, "D3DXQuaternionInverse"));
	original_D3DXQuaternionMultiply = reinterpret_cast<D3DXQUATERNION*  (WINAPI*)(  D3DXQUATERNION *pOut,   CONST D3DXQUATERNION *pQ1,   CONST D3DXQUATERNION *pQ2 )>(GetProcAddress(d3d9x_module, "D3DXQuaternionMultiply"));
	original_D3DXQuaternionNormalize = reinterpret_cast<D3DXQUATERNION*  (WINAPI*)(  D3DXQUATERNION *pOut,   CONST D3DXQUATERNION *pQ )>(GetProcAddress(d3d9x_module, "D3DXQuaternionNormalize"));
	original_D3DXQuaternionRotationAxis = reinterpret_cast<D3DXQUATERNION*  (WINAPI*)(  D3DXQUATERNION *pOut,   CONST D3DXVECTOR3 *pV,   FLOAT Angle )>(GetProcAddress(d3d9x_module, "D3DXQuaternionRotationAxis"));
	original_D3DXQuaternionRotationMatrix = reinterpret_cast<D3DXQUATERNION*  (WINAPI*)(  D3DXQUATERNION *pOut,   CONST D3DXMATRIX *pM)>(GetProcAddress(d3d9x_module, "D3DXQuaternionRotationMatrix"));
	original_D3DXQuaternionToAxisAngle = reinterpret_cast<void  (WINAPI*)(  CONST D3DXQUATERNION *pQ,   D3DXVECTOR3 *pAxis,   FLOAT *pAngle )>(GetProcAddress(d3d9x_module, "D3DXQuaternionToAxisAngle"));
	original_D3DXSaveSurfaceToFileW = reinterpret_cast<HRESULT  (WINAPI*)(  LPCWSTR    pDestFile,   D3DXIMAGE_FILEFORMAT      DestFormat,   LPDIRECT3DSURFACE9  pSrcSurface,   CONST PALETTEENTRY*       pSrcPalette,   CONST RECT*      pSrcRect)>(GetProcAddress(d3d9x_module, "D3DXSaveSurfaceToFileW"));
	original_D3DXVec3Normalize = reinterpret_cast<D3DXVECTOR3*  (WINAPI*)(  D3DXVECTOR3 *pOut,   CONST D3DXVECTOR3 *pV )>(GetProcAddress(d3d9x_module, "D3DXVec3Normalize"));
	original_D3DXVec3Transform = reinterpret_cast<D3DXVECTOR4*  (WINAPI*)(  D3DXVECTOR4 *pOut,   CONST D3DXVECTOR3 *pV,   CONST D3DXMATRIX *pM )>(GetProcAddress(d3d9x_module, "D3DXVec3Transform"));

	return TRUE;
}

void dispose()
{
}

// DLLエントリポイント
BOOL APIENTRY DllMain(HINSTANCE, DWORD reason, LPVOID)
{
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		init();
	case DLL_PROCESS_DETACH:
		dispose();
	}
	return TRUE;
}
