/**\file loadModelFile.h*/
#include "engine_pch.h"
#include "core/assimpLoader/assimpLoaderLog.h"
namespace Engine {

	namespace Loader {

		static void loadMeshIndicies(aiMesh* mesh, std::vector<uint32_t>& indicies, bool shouldLog = false) { //!<load mesh data
			aiFace* face = nullptr;
			//for each face of the mesh
			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				//get all the indicies and put them into the vector
				face = &mesh->mFaces[i];
				for (unsigned int j = 0; j < face->mNumIndices; j++) {
					unsigned int indicy = face->mIndices[j];
					indicies.push_back(indicy);
					Log::debug("Size: {}", indicies.size());
					Log::debug(face->mIndices[j]);
				}
			}

		}

		static void loadMeshVerticies(aiMesh* mesh, std::vector<float>& verticies, bool shouldLog = false) { //!<load mesh data
			
			if (!mesh->HasPositions()) {
				Log::error("Mesh '{}' has no vertexes.", mesh->mName.C_Str());
				return;
			}
			else if (shouldLog) {
				Log::debug("Mesh '{}' has vertexes.", mesh->mName.C_Str());
			}

			if (!mesh->HasNormals()) {
				Log::error("Mesh '{}' has no vertex normals.", mesh->mName.C_Str());
				return;
			}
			else if (shouldLog) {
				Log::debug("Mesh '{}' has vertex normals.", mesh->mName.C_Str());
			}

			if (!mesh->mTextureCoords) {
				Log::error("Mesh '{}' has no UV's.", mesh->mName.C_Str());
				return;
			}
			else if (shouldLog) {
				Log::debug("Mesh '{}' has UV's.", mesh->mName.C_Str());
			}
			Log::debug("Number of Vertexes: {}", mesh->mNumVertices);
			//Log::debug("Number of UV's: {}", mesh->mTextureCoords);
			Log::debug("Number of UV channels: {}", mesh->GetNumUVChannels());

			//for each vertex of the mesh
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				verticies.push_back(mesh->mVertices[i].x);
				verticies.push_back(mesh->mVertices[i].y);
				verticies.push_back(mesh->mVertices[i].z);
				verticies.push_back(mesh->mNormals[i].x);
				verticies.push_back(mesh->mNormals[i].y);
				verticies.push_back(mesh->mNormals[i].z);
				//verticies.push_back(0.0f);
				//verticies.push_back(0.0f);
				verticies.push_back(mesh->mTextureCoords[0][i].x);
				verticies.push_back(mesh->mTextureCoords[0][i].y);

			}

		}




		static void loadModelFile(const std::string& filePath, std::vector<uint32_t>& indicies, std::vector<float>& verticies, bool shouldLog = false) { //!<loads a model from a file 

			// Clear tmpMesh
			indicies.clear();
			verticies.clear();
			//load the file
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(filePath, aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_Triangulate);

			//log issues if present
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				Log::error("Cannot load: {0}, ASSIMP Error {1}", filePath, importer.GetErrorString());
				return;
			}
			else {
				Log::debug("File '{}' loaded successfully", filePath);
			}

			//load all meshes
			for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
				if (scene->mMeshes[i]->HasPositions()) {
					loadMeshIndicies(scene->mMeshes[i], indicies, shouldLog);
					loadMeshVerticies(scene->mMeshes[i], verticies, shouldLog);
				}
			}
			if (shouldLog) {
				Log::debug("Indicies:");
				for (unsigned int i = 0; i < indicies.size(); i += 3) {
					Log::debug("{} {} {}", indicies[i], indicies[i + 1], indicies[i + 2]);
				}
				Log::debug("Verticies:");
				for (unsigned int i = 0; i < verticies.size(); i += 8) {
					Log::debug("{} {} {} {} {} {} {} {}", 
						verticies[i + 0], verticies[i + 1], verticies[i + 2],
						verticies[i + 3], verticies[i + 4], verticies[i + 5],
						verticies[i + 6], verticies[i + 7]
					);
				}
			}
		}

	}

}