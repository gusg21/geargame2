/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_internal.h"

/* TODO: Macro? */

#import <Cocoa/Cocoa.h>

typedef enum
{
    FDT_SAVE,
    FDT_OPEN,
    FDT_OPENFOLDER
} cocoa_FileDialogType;

void show_file_dialog(cocoa_FileDialogType type, SDL_DialogFileCallback callback, void* userdata, SDL_Window* window, const SDL_DialogFileFilter *filters, const char* default_location, SDL_bool allow_many)
{
    /* NSOpenPanel inherits from NSSavePanel */
    NSSavePanel *dialog;
    NSOpenPanel *dialog_as_open;

    switch (type) {
    case FDT_SAVE:
        dialog = [NSSavePanel savePanel];
        break;
    case FDT_OPEN:
        dialog_as_open = [NSOpenPanel openPanel];
        [dialog_as_open setAllowsMultipleSelection:((allow_many == SDL_TRUE) ? YES : NO)];
        dialog = dialog_as_open;
        break;
    case FDT_OPENFOLDER:
        dialog_as_open = [NSOpenPanel openPanel];
        [dialog_as_open setCanChooseFiles:NO];
        [dialog_as_open setCanChooseDirectories:YES];
        [dialog_as_open setAllowsMultipleSelection:((allow_many == SDL_TRUE) ? YES : NO)];
        dialog = dialog_as_open;
        break;
    };

    int n = -1;
    while (filters[++n].name && filters[n].pattern);
    NSMutableArray *types = [[NSMutableArray alloc] initWithCapacity:n ];

    int has_all_files = 0;
    for (int i = 0; i < n; i++) {
        char *pattern = SDL_strdup(filters[i].pattern);
        char *pattern_ptr = pattern;

        if (!pattern_ptr) {
            SDL_OutOfMemory();
            callback(userdata, NULL, -1);
            return;
        }

        for (char *c = pattern; *c; c++) {
            if (*c == ';') {
                *c = '\0';
                [types addObject: [NSString stringWithFormat: @"%s", pattern_ptr]];
                pattern_ptr = c + 1;
            } else if (!((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z') || (*c >= '0' && *c <= '9') || *c == '.' || *c == '_' || *c == '-' || (*c == '*' && (c[1] == '\0' || c[1] == ';')))) {
                SDL_SetError("Illegal character in pattern name: %c (Only alphanumeric characters, periods, underscores and hyphens allowed)", *c);
                callback(userdata, NULL, -1);
                SDL_free(pattern);
            } else if (*c == '*') {
                has_all_files = 1;
            }
        }
        [types addObject: [NSString stringWithFormat: @"%s", pattern_ptr]];

        SDL_free(pattern);
    }

    if (!has_all_files) {
        if (@available(macOS 11.0, *)) {
            [dialog setAllowedContentTypes:types];
        } else {
            [dialog setAllowedFileTypes:types];
        }
    }

    /* Keep behavior consistent with other platforms */
    [dialog setAllowsOtherFileTypes:YES];

    if (default_location) {
        [dialog setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:default_location]]];
    }

    NSWindow *w = NULL;

    if (window) {
        w = (__bridge NSWindow *)SDL_GetProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, NULL);
    }

    if (w) {
        // [dialog beginWithCompletionHandler:^(NSInteger result) {
        [dialog beginSheetModalForWindow:w completionHandler:^(NSInteger result) {
            // NSModalResponseOK for >= 10.13
            if (result == NSFileHandlingPanelOKButton) {
                if (dialog_as_open) {
                    NSArray* urls = [dialog_as_open URLs];
                    const char *files[[urls count] + 1];
                    for (int i = 0; i < [urls count]; i++) {
                        files[i] = [[[urls objectAtIndex:i] path] UTF8String];
                    }
                    files[[urls count]] = NULL;
                    callback(userdata, files, -1);
                } else {
                    const char *files[2] = { [[[dialog URL] path] UTF8String], NULL };
                    callback(userdata, files, -1);
                }
            } else if (result == NSModalResponseCancel) {
                const char *files[1] = { NULL };
                callback(userdata, files, -1);
            }
        }];
    } else {
        // NSModalResponseOK for >= 10.10
        if ([dialog runModal] == NSOKButton) {
            if (dialog_as_open) {
                NSArray* urls = [dialog_as_open URLs];
                const char *files[[urls count] + 1];
                for (int i = 0; i < [urls count]; i++) {
                    files[i] = [[[urls objectAtIndex:i] path] UTF8String];
                }
                files[[urls count]] = NULL;
                callback(userdata, files, -1);
            } else {
                const char *files[2] = { [[[dialog URL] path] UTF8String], NULL };
                callback(userdata, files, -1);
            }
        } else {
            const char *files[1] = { NULL };
            callback(userdata, files, -1);
        }
    }
}

void SDL_ShowOpenFileDialog(SDL_DialogFileCallback callback, void* userdata, SDL_Window* window, const SDL_DialogFileFilter *filters, const char* default_location, SDL_bool allow_many)
{
    show_file_dialog(FDT_OPEN, callback, userdata, window, filters, default_location, allow_many);
}

void SDL_ShowSaveFileDialog(SDL_DialogFileCallback callback, void* userdata, SDL_Window* window, const SDL_DialogFileFilter *filters, const char* default_location)
{
    show_file_dialog(FDT_SAVE, callback, userdata, window, filters, default_location, 0);
}

void SDL_ShowOpenFolderDialog(SDL_DialogFileCallback callback, void* userdata, SDL_Window* window, const char* default_location, SDL_bool allow_many)
{
    show_file_dialog(FDT_OPENFOLDER, callback, userdata, window, NULL, default_location, allow_many);
}
