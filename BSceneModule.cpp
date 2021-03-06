//
// BSceneModule
//

#include <cstdio>

//#include "stdafx.h"
#include "BSceneModule.h"
#include "BTextures.h"
#include "BGame.h"


//*****************************************************************************
void BSceneModule::DestroyCurrentScene() {
  // Delete current objects to prepare for new scene
  //if(!m_sSceneName.IsEmpty()) {
  if(!m_sSceneName.empty()) {
    // BTextures::DeleteTexturesMarked(m_sSceneName);
  }
  delete [] m_pObject;
  m_pObject = 0;
  m_nObjects = 0;
}


//*****************************************************************************
void BSceneModule::LoadScene(string sSceneName) {
  //
  // Open Scene file and load all referenced objects and textures.
  //

  // Get rid of current scene
  DestroyCurrentScene();

  // Always load the GasStation.Object
  // LoadObject(sSceneName, "GasStation.Object", true);

  // Load scene and its objects
  m_sSceneName = sSceneName;
  // m_nObjects = CountObjects(sSceneName);
  m_pObject = new BObject[m_nObjects];

  if(LoadCommonSceneParams(sSceneName)) {
    LoadObjects(sSceneName);  
  }
}

//*****************************************************************************
bool BSceneModule::LoadCommonSceneParams(string sSceneName) {
  FILE *fp;
  string sFile = sSceneName + ".Scene";

  //fp = fopen(sFile, "r");
  fp = fopen(sFile.c_str(), "r");
  if(fp) {
    char sLine[1024];
    char *p = fgets(sLine, 1024, fp);
    while(p) {
      string sTmp = sLine;
      //if(sTmp.Find("//", 0) == 0) {
      if(sTmp.find("//", 0) == 0) {
        // Comment line, skip it
        p = fgets(sLine, 1024, fp);
      //} else if(sTmp.Find("[ORIGIN]", 0) != -1) {
      } else if(sTmp.find("[ORIGIN]", 0) != -1) {
        p = ReadVectors(fp, &m_vOrigin, 1);
      } else {
        // No known tag found, skip the line
        p = fgets(sLine, 1024, fp);
      }
    }
    fclose(fp);
  } else {
    string sMsg;
    //sMsg.Format("Cannot open scene file %s!", sFile);
    sMsg.assign("Cannot open scene file ");
    sMsg.append(sFile);
    sMsg.append("!");
    BGame::MyAfxMessageBox(sMsg);
  }
  return true;
}

//*****************************************************************************
bool BSceneModule::LoadObjects(string sSceneName) {
  return false;
}

//*****************************************************************************
char *BSceneModule::ReadVectors(FILE *fp, BVector *pVectors, int nMaxToRead) {
  return 0;
}
