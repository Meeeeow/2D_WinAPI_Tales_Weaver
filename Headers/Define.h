#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 800
#define WINCY 600

#define SAFE_DELETE(p) if(p) {delete p; p=nullptr; }
#define SAFE_DELETE_ARR(p) if(p) {delete[] p; p=nullptr; }

#define OBJ_NOEVENT	0
#define OBJ_DEAD	1

// 타일 크기
#define TILECX 30
#define TILECY 30

#endif // !__DEFINE_H__
