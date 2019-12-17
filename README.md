# MovieClip 2D sprite width WebGL!

Hello! I will present a small class that displays a sprite on a WebGL screen with a texture:
As promised, I am opening you the MovieClip class for WebGL. To initialize the class, use the following:

```C++
clip = new MovieClip(gl,2036,2032); //gl - WebGLRenderingContext, 2036 - width, 2032 - height
clip->loadSprite("background.jpg",0); "background.jpg" - image url (string), 0 - clipType (int)
clip->loadMovieClip("video.webm",1); "video.webm" - video url (string), 1 - clipType (int)
```

You need to add an event to download:

Image event
```C++
clip->getImageElement()->addEventListener("load",cheerp::Callback(isImageLoaded));
```

Video event
```C++
clip->getVideoElement()->addEventListener("loadeddata",cheerp::Callback(onAnimLoad));
```

Sample event image loaded
```C+
void Scene::isImageLoaded(Event* e)
{
HTMLImageElement* target=(HTMLImageElement*)e->get_target();
int clipIndex = parseInt(target->getAttribute("clipID"));
target->removeEventListener("load",cheerp::Callback(isImageLoaded));
clip->set_timeupdate(true);
clip->set_playing(true);
clip->checkReady();
clip->updateTexture();
}
```

There are other options for adding a boot event, I will try to use this trick in other lessons.

## Links
* [YouTube channel](https://www.youtube.com/watch?v=UeEl_2h4rmk)
* [Cheerp site](http://cheerp.ru/archives/129)
