#include "TileMap.h"


//void TileMap::LoadMap(const char* fileName)
//{
	// Homework:
	// Add code here so we can read values from a txt file
	// to load the textures and map tiles.

	// fopen/fclose/fscanf - C way
	// fstream - C++ way

//}

void TileMap::Load(const std::filesystem::path& mapName, const std::filesystem::path& tilesetName)
{
	LoadMap(mapName);
	LoadTextures(tilesetName);
}


void TileMap::LoadMap(const std::filesystem::path& fileName)
{
	if (mMap)
	{
		mMap.reset();
	}

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	fscanf_s(file, "Columns: %d\n", &mColumns);
	fscanf_s(file, "Rows: %d\n", &mRows);

	mMap = std::make_unique<int[]>(mColumns * mRows);
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y);
			mMap[index] = fgetc(file) - '0';
		}
		fgetc(file);
	}

	fclose(file);
}
void TileMap::LoadTextures(const std::filesystem::path& fileName)
{
	mTiles.clear();

	FILE* file = nullptr;
	fopen_s(&file, fileName.u8string().c_str(), "r");

	int count = 0;
	fscanf_s(file, "Count: %d\n", &count);

	for (int i = 0;i < count; ++i)
	{
		char buffer[256];
		fscanf_s(file, "%s\n", buffer, static_cast<int>(std::size(buffer)));

		mTiles.push_back(X::LoadTexture(buffer));
	}

	fclose(file);

	//cache the tile dimensions
	mTileWidth = X::GetSpriteWidth(mTiles[0]);
	mTileHeight = X::GetSpriteHeight(mTiles[0]);
}


void TileMap::Render() const
{
	// Homework:
	// Add code to draw the tile map.
	// for (y from 0 to mRows)
	//   for (x from 0 to mColumns)
	// 	   Compute pixel positions from the tile index
	//	   DrawSprite(textureId, {pixelX, pixelY}, X::Pivot::TopLeft)
	// 
	// 	Note that this will not work as we need pixel positions!
	//		DrawSprite(textureId, {x, y} ... )
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int mapIndex = GetIndex(x, y);
			const int tileIndex = mMap[mapIndex];
			const X::TextureId textureId = mTiles.at(tileIndex);
			const X::Math::Vector2 worldPosition = { x * 32.0f, y * 32.0f };

			//TODO:
			//Get screenPosition from camera
			X::DrawSprite(textureId, worldPosition, X::Pivot::TopLeft);
		}
	}

}

bool TileMap::IsBlocked(int x, int y) const
{
	const int index = x + (y * mColumns);
	const int tileType = mMap[index];
	if (tileType == 0 || tileType == 1)
	{
		return false;
	}
	return true;
}

float TileMap::GetTraversalCost(int x, int y) const
{
	const int index = x + (y * mColumns);
	const int tileType = mMap[index];
	if (tileType == 0)
		return 1.0f;
	return 3.0f;
}

float TileMap::GetTraversalCost(int fromX, int fromY, int toX, int toY) const
{
	float tileCost = GetTraversalCost(toX, toY);

	//            1
	//            ^  1.414f = sqrt(2)
	//           \|/
	//           -*-> 1
	//           /|\
	//
	bool isDiagonal = (fromX != toX) && (fromY != toY);
	return tileCost * (isDiagonal ? 1.414f : 1.0f);
}

int TileMap::GetIndex(int column, int row)const
{
	return column + (row * mColumns);
}